Run `make` to build the `events` program.

Run `make test` to build and run the tests. The output should be:
```
PASS sensor: 91.0 C reads back as 91.0
PASS sensor: 40.0 %RH reads back as 40.0
PASS sensor: the timestamp is stored
PASS sensor: 0.0 C reads back as 0.0
PASS sensor: 100.0 C reads back as 100.0
PASS sensor: a failed read returns the iom361 code
PASS sensor: a failed read changes nothing
PASS panel: a press is pressed
PASS panel: a press is not released
PASS panel: a release is released
PASS panel: a release is not pressed
PASS panel: a held switch is not pressed
PASS panel: a held switch is not released
PASS panel: press and release in one step
PASS panel_led: turning LED 1 on keeps the others
PASS panel_led: turning LED 2 off keeps the others
PASS panel_toggle: toggling LED 0 keeps the others
PASS panel_toggle: toggling twice restores the LEDs
PASS panel_led: n = 32 is rejected
PASS panel_led: n = -1 is rejected
PASS panel_toggle: n = 32 is rejected
PASS scenario: a load with comments and blank lines
PASS scenario: values hold between lines
PASS scenario: a line is in force at its own tick
PASS scenario: the last line holds after it
PASS scenario: a scenario without a start line
PASS scenario: a line with a missing field
PASS scenario: ticks that do not increase
PASS scenario: ticks that go backward
PASS scenario: a file that does not exist
30 passed, 0 failed
sh regress.sh
PASS basic.txt
PASS midnight.txt
```