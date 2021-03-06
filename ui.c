#include <stdio.h>
#include <string.h>

#include "ui.h"

/* Constants */
static const char *const WifiIcon = "";
static const char *const MemoryIcon = "";
static const char *const DiskIcon = "";
static const char *const CPUIcon = "";
static const char *const SpeakerIconUnmuted = "";
static const char *const SpeakerIconMuted = "";
static const char *const DateIcon = "";
static const char *const TimeIcon = "";
static const char *const TimeIconWithSpace = " ";
static const char *const BatteryIconCharging = "";
static const char *const BatteryIcon100 = "";
static const char *const BatteryIcon75 = "";
static const char *const BatteryIcon50 = "";
static const char *const BatteryIcon25 = "";
static const char *const BatteryIcon0 = "";
static const char *const TimeFormat = "%l:%M %p";
static const char *const DateFormat = "%A, %B %d %Y";
static const char *const BlueFG = "^c#4e8cb7^";
static const char *const LightBlueFG = "^c#68a7d4^";
static const char *const WhiteFG = "^c#ffffff^";
static const char *const BlackFG = "^c#4d5261^";
static const char *const PinkFG = "^c#f7a8b8^";
static const char *const OrangeFG = "^c#eb8e54^";
static const char *const SchemeReset = "^d^";
static const float Gigabyte = 1024 * 1024 * 1024;

void setOutput(dwmStatus *status)
{
    int volume, usedMemory, totalMemory, usedDisk, totalDisk, outputLength;

    volume = status->volume.percent + 0.5;
    usedMemory = status->memory.usedBytes / Gigabyte + 0.5;
    totalMemory = status->memory.totalBytes / Gigabyte + 0.5;
    usedDisk = status->disk.usedBytes / Gigabyte + 0.5;
    totalDisk = status->disk.totalBytes / Gigabyte + 0.5;

    if (status->wifi.active) {
        outputLength = strlen(status->output);
        snprintf(status->output + outputLength,
                 MAX_STATUS_OUTPUT - outputLength,
                 "%s%s%s %.1f%%  ", BlueFG, status->wifi.icon, SchemeReset, status->wifi.strength);
    }

    outputLength = strlen(status->output);
    snprintf(status->output + outputLength, MAX_STATUS_OUTPUT - outputLength,
             "%s%s%s %.1f%%  %s%s%s %d/%dG  %s%s%s %d/%dG  %s%s%s %d%%  ",
             BlueFG, status->cpu.icon, SchemeReset, status->cpu.utilization,
             BlueFG, status->memory.icon, SchemeReset, usedMemory, totalMemory,
             BlueFG, status->disk.icon, SchemeReset, usedDisk, totalDisk,
             BlueFG, status->volume.icon, SchemeReset, volume);

    if (status->battery.active) {
        outputLength = strlen(status->output);
        snprintf(status->output + outputLength,
                 MAX_STATUS_OUTPUT - outputLength, "%s%s%s %.0f%%  ",
                 BlueFG, status->battery.icon, SchemeReset, status->battery.percent);
    }

    outputLength = strlen(status->output);
    snprintf(status->output + outputLength, MAX_STATUS_OUTPUT - outputLength,
             "%s%s%s %s  %s%s%s%s",
             BlueFG, status->date.icon, SchemeReset, status->date.output,
             BlueFG, status->time.icon, SchemeReset, status->time.output);
}

void setDateFormat(dwmDate *date)
{
    date->format = DateFormat;
}

void setTimeFormat(dwmTime *time)
{
    time->format = TimeFormat;
}

void setBatteryIcon(dwmBattery *battery)
{
    if (battery->charging) {
        battery->icon = BatteryIconCharging;
    } else {
        switch ((int)battery->percent) {
        case 90 ... 100:
            battery->icon = BatteryIcon100;
            break;
        case 60 ... 89:
            battery->icon = BatteryIcon75;
            break;
        case 30 ... 59:
            battery->icon = BatteryIcon50;
            break;
        case 10 ... 29:
            battery->icon = BatteryIcon25;
            break;
        default:
            battery->icon = BatteryIcon0;
            break;
        }
    }
}

void setCPUIcon(dwmCPU *cpu)
{
    cpu->icon = CPUIcon;
}

/*
 * Provides consistent spacing between the time icon and time value
 * for both single and double digit hours throughout the day.
 * All double digit hours are prefixed with an empty space.
 */
void setTimeIcon(dwmTime *time)
{
    time->icon = time->output[0] != ' ' ? TimeIconWithSpace : TimeIcon;
}

void setDateIcon(dwmDate *date)
{
    date->icon = DateIcon;
}

void setDiskIcon(dwmDisk *disk)
{
    disk->icon = DiskIcon;
}

void setMemoryIcon(dwmMemory *memory)
{
    memory->icon = MemoryIcon;
}

void setVolumeIcon(dwmVolume *volume)
{
    volume->icon = volume->muted ? SpeakerIconUnmuted : SpeakerIconMuted;
}

void setWifiIcon(dwmWifi *wifi)
{
    wifi->icon = WifiIcon;
}
