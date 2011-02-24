#include <stdlib.h>
#include <stdio.h>

#define TIME_LEN 20

struct clock_time {
    int hh, mm, ss;
};

typedef struct clock_time clock_time;

clock_time get_time(char *time_str) {
    clock_time time_num;
    
    char temp_seg[3];
    temp_seg[2] = '\0';
    
    temp_seg[0] = time_str[0];
    temp_seg[1] = time_str[1];
    time_num.hh = atoi(temp_seg);
    
    temp_seg[0] = time_str[3];
    temp_seg[1] = time_str[4];
    time_num.mm = atoi(temp_seg);
    
    temp_seg[0] = time_str[6];
    temp_seg[1] = time_str[7];
    time_num.ss = atoi(temp_seg);
    
    return time_num;
}

int time_diff(char *start, char*fin) {
    clock_time num_start, num_fin;
    num_start = get_time(start);
    num_fin = get_time(fin);
    
    int total_sec = 0;
    
    int borrow_sec = 0;
    if (num_start.ss <= num_fin.ss) {
        total_sec += num_fin.ss - num_start.ss;
    }
    else {
        total_sec += (60 + num_fin.ss - num_start.ss);
        borrow_sec = 1;
    }
    
    int borrow_min = 0;
    if (borrow_sec == 1)  {
        if (num_fin.mm == 0) {
            total_sec += 60 * (59 - num_start.mm);
            borrow_min = 1;
        }
        else {
             if (num_start.mm <= num_fin.mm - 1) {
                total_sec += 60 * (num_fin.mm - num_start.mm - 1);
            }
            else {
                total_sec += 60 * (60 + num_fin.mm - num_start.mm - 1);
                borrow_min = 1;
            }
        }
    }
    else {
        if (num_start.mm <= num_fin.mm) {
            total_sec += 60 * (num_fin.mm - num_start.mm);
        }
        else {
            total_sec += 60 * (60 + num_fin.mm - num_start.mm);
            borrow_min = 1;
        }
    }
    
    int borrow_hr = 0;
    if (borrow_min == 1)  {
        if (num_fin.hh == 0) {
            total_sec +=3600 * (23 - num_start.hh);
            borrow_hr = 1;  
        }
        else {
             if (num_start.hh <= num_fin.hh - 1) {
                total_sec += 3600 * (num_fin.hh - num_start.hh - 1);
            }
            else {
                total_sec += 3600 * (24 + num_fin.hh - num_start.hh - 1);
                borrow_hr = 1;
            }
        }
    }
    else {
        if (num_start.hh <= num_fin.hh) {
            total_sec += 3600 * (num_fin.hh - num_start.hh);
        }
        else {
            total_sec += 3600 * (24 + num_fin.hh - num_start.hh);
            borrow_hr = 1;
        }
    }
    
    return total_sec;
}

int main(int argc, char **argv) {
    char time1[TIME_LEN], time2[TIME_LEN];
    scanf("%s %s", time1, time2);
    printf("%d\n", time_diff(time1, time2));
    return 0;
}

