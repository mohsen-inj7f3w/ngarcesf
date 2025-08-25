#ifndef _I3STATUS_H
#define _I3STATUS_H

#include <stdbool.h>

#include "queue.h"

#define BAR "^fg(#333333)^p(5;-2)^ro(2)^p()^fg()^p(5)"
#define BEGINS_WITH(haystack, needle) (strncmp(haystack, needle, strlen(needle)) == 0)
#define max(a, b) (a > b ? a : b)

typedef enum { CS_DISCHARGING, CS_CHARGING, CS_FULL } charging_status_t;
enum { ORDER_RUN, ORDER_WLAN, ORDER_ETH, ORDER_BATTERY, ORDER_CPU_TEMPERATURE, ORDER_LOAD, ORDER_TIME, MAX_ORDER };

struct battery {
        char *path;
        /* Use last full capacity instead of design capacity */
        bool use_last_full;
        SIMPLEQ_ENTRY(battery) batteries;
};

/* src/general.c */
char *skip_character(char *input, char character, int amount);
void die(const char *fmt, ...);
char *concat(const char *str1, const char *str2);
void create_file(const char *name);
void setup(void);
void write_to_statusbar(const char *name, const char *message, bool final_entry);
void slurp(char *filename, char *destination, int size);

/* src/output.c */
void write_error_to_statusbar(const char *message);
char *color(const char *colorstr);
void cleanup_rbar_dir();

/* src/config.c */
int load_configuration(const char *configfile);

const char *get_ipv6_addr();
const char *get_battery_info(struct battery *bat);
const char *get_ip_addr();
const char *get_wireless_info();
const char *get_cpu_temperature_info();
const char *get_eth_info();
const char *get_load();
bool process_runs(const char *path);

SIMPLEQ_HEAD(battery_head, battery);
extern struct battery_head batteries;

/* socket file descriptor for general purposes */
extern int general_socket;

extern const char *wlan_interface;
extern const char *eth_interface;
extern const char *wmii_path;
extern const char *time_format;
extern bool use_colors;
extern bool get_ethspeed;
extern bool get_cpu_temperature;
extern char *thermal_zone;
extern const char *wmii_normcolors;
extern char order[MAX_ORDER][2];
extern const char **run_watches;
extern unsigned int num_run_watches;
extern unsigned int interval;

#endif
