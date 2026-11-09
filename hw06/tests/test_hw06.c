#include <stdio.h>
#include <stdbool.h>
#include "sensor.h"
#include "panel.h"
#include "scenario.h"
#include "iom361_r4.h"
 
#define TMP_FILE "tests/tmp_scenario.txt"
 
static int passed = 0;
static int failed = 0;
static scenario_t sc;
 
static void check(const char *name, bool ok){
    printf("%s %s\n", ok ? "PASS" : "FAIL", name);
    if(ok)
        passed++;
    else
        failed++;
}
 
static void write_file(const char *text){
    FILE *f = fopen(TMP_FILE, "w");
    if(f != NULL){
        fputs(text, f);
        fclose(f);
    }
}
 
static uint32_t *setup(void){
    int rc;
    uint32_t *base = iom361_initialize(4, 4, &rc);
    iom361_set_display(false);
    return base;
}
 
static void test_sensor(void){
    uint32_t *base = setup();
    reading_t r;
 
    _iom361_set_sensor1(91.0f, 40.0f);
    int rc = sensor_read(base, 100, &r);
    check("sensor: 91.0 C reads back as 91.0", rc == 0 && r.temp_c == 91.0f);
    check("sensor: 40.0 %RH reads back as 40.0", rc == 0 && r.rh_pct == 40.0f);
    check("sensor: the timestamp is stored", rc == 0 && r.t == 100);
 
    _iom361_set_sensor1(0.0f, 0.0f);
    rc = sensor_read(base, 100, &r);
    check("sensor: 0.0 C reads back as 0.0", rc == 0 && r.temp_c == 0.0f);
 
    _iom361_set_sensor1(100.0f, 50.0f);
    rc = sensor_read(base, 100, &r);
    check("sensor: 100.0 C reads back as 100.0", rc == 0 && r.temp_c == 100.0f);
 
    uint32_t wrong_base[8];
    reading_t before = {123, 1.5f, 2.5f};
    reading_t after = before;
    rc = sensor_read(wrong_base, 999, &after);
    check("sensor: a failed read returns the iom361 code", rc == 1);
    check("sensor: a failed read changes nothing",
          after.t == before.t && after.temp_c == before.temp_c && after.rh_pct == before.rh_pct);
}
 
static void test_pressed_released(void){
    check("panel: a press is pressed", panel_pressed(0x1, 0x0) == 0x1);
    check("panel: a press is not released", panel_released(0x1, 0x0) == 0x0);
    check("panel: a release is released", panel_released(0x0, 0x1) == 0x1);
    check("panel: a release is not pressed", panel_pressed(0x0, 0x1) == 0x0);
    check("panel: a held switch is not pressed", panel_pressed(0x1, 0x1) == 0x0);
    check("panel: a held switch is not released", panel_released(0x1, 0x1) == 0x0);
    check("panel: press and release in one step", panel_pressed(0x6, 0x5) == 0x2 && panel_released(0x6, 0x5) == 0x1);
}
 
static void test_leds(void){
    uint32_t *base = setup();
    int rc;
 
    iom361_writeReg(base, LEDS_REG, 0x5, &rc);
    panel_led(base, 1, 1);
    check("panel_led: turning LED 1 on keeps the others", iom361_readReg(base, LEDS_REG, &rc) == 0x7);
 
    panel_led(base, 2, 0);
    check("panel_led: turning LED 2 off keeps the others", iom361_readReg(base, LEDS_REG, &rc) == 0x3);
 
    iom361_writeReg(base, LEDS_REG, 0x5, &rc);
    panel_toggle(base, 0);
    check("panel_toggle: toggling LED 0 keeps the others", iom361_readReg(base, LEDS_REG, &rc) == 0x4);
 
    panel_toggle(base, 0);
    check("panel_toggle: toggling twice restores the LEDs", iom361_readReg(base, LEDS_REG, &rc) == 0x5);
 
    check("panel_led: n = 32 is rejected", panel_led(base, 32, 1) == -1);
    check("panel_led: n = -1 is rejected", panel_led(base, -1, 1) == -1);
    check("panel_toggle: n = 32 is rejected", panel_toggle(base, 32) == -1);
}
 
static void test_scenario(void){
    write_file("# a comment\n"
               "\n"
               "start 1791273600   # 2026-10-06 08:00:00 UTC\n"
               "\n"
               "# tick temp rh switches\n"
               "0   21.5   40   0x0\n"
               "\n"
               "5   22.0   41   0x1   # switch 0 on\n");
    int rc = scenario_load(TMP_FILE, &sc);
    check("scenario: a load with comments and blank lines", rc == 0 && sc.count == 2 && sc.start == 1791273600);
 
    const scenario_line_t *line = line_in_force(&sc, 3);
    check("scenario: values hold between lines", line != NULL && line->tick == 0 && line->temp == 21.5f);
 
    line = line_in_force(&sc, 5);
    check("scenario: a line is in force at its own tick", line != NULL && line->tick == 5 && line->switches == 0x1);
 
    line = line_in_force(&sc, 60);
    check("scenario: the last line holds after it", line != NULL && line->tick == 5);
 
    write_file("# no start line\n"
               "0   21.5   40   0x0\n");
    check("scenario: a scenario without a start line", scenario_load(TMP_FILE, &sc) == 2);
 
    write_file("start 1791273600\n"
               "0   21.5   40   0x0\n"
               "1   21.5   0x1\n");
    check("scenario: a line with a missing field", scenario_load(TMP_FILE, &sc) == 3);
 
    write_file("start 1791273600\n"
               "0   21.5   40   0x0\n"
               "5   21.5   40   0x1\n"
               "5   21.5   40   0x0\n");
    check("scenario: ticks that do not increase", scenario_load(TMP_FILE, &sc) == 4);
 
    write_file("start 1791273600\n"
               "0   21.5   40   0x0\n"
               "5   21.5   40   0x1\n"
               "3   21.5   40   0x0\n");
    check("scenario: ticks that go backward", scenario_load(TMP_FILE, &sc) == 4);
 
    check("scenario: a file that does not exist", scenario_load("tests/no_such_file.txt", &sc) == -1);
 
    remove(TMP_FILE);
}
 
int main(void){
    test_sensor();
    test_pressed_released();
    test_leds();
    test_scenario();
    printf("%d passed, %d failed\n", passed, failed);
    return failed == 0 ? 0 : 1;
}