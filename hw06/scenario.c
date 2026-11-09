#include "scenario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LINE_SIZE 500

const scenario_line_t* line_in_force(const scenario_t* s, int tick){
    const scenario_line_t* result = NULL;

    for(int i = 0; i < s->count; i++){
        if(s->lines[i].tick > tick){
            break;
        }
        result = &s->lines[i];
    }
    return result;
}

int scenario_load(const char* path, scenario_t* s){
    FILE* file = fopen(path, "r");
    if(file == NULL)
       return -1;

    s->count = 0;
    int line_count = 0;
    char line[LINE_SIZE];
    char scan[2];
    bool has_start = false;
    long long start;


    while(fgets(line, sizeof(line),file)){
        line_count++;
        char* hashtag = strchr(line, '#');
        if (hashtag != NULL){
            *hashtag = '\0';
        }
        if(sscanf(line, " %1s", scan) != 1)
            continue;
        if(has_start == false){
            if(sscanf(line, " start %lld", &start) != 1){
                fclose(file);
                return line_count;
            }
            s->start = start;
            has_start = true; 
            continue;
        }
        int tick; 
        float temp, rh; 
        uint32_t switches; 
        if(sscanf(line, "%d %f %f %x", &tick, &temp, &rh, &switches) != 4){
            fclose(file);
            return line_count;
        }
        if(s->count > 0){
            if(tick <= s->lines[s->count -1].tick){
                fclose(file);
                return line_count;
            }
        }
        if(s->count == MAX_LINES){
            fclose(file);
            return line_count;
        }
        s->lines[s->count].tick = tick; 
        s->lines[s->count].temp = temp;
        s->lines[s->count].rh = rh;
        s->lines[s->count].switches = switches;
        s->count++;

    }
    if(has_start == false){
        fclose(file);
        return ++line_count;
    }
        
    fclose(file);
    return 0;
}