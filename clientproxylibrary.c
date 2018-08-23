//
#include "clientproxylibrary.h"
#include "alarmClockStubs.h"
#include <stdio.h>
#include <glib.h>
#include <gio/gio.h>

static const char* name="com.time.service.alarmClock";
static const char* path="/com/time/service/manager/Object";
static GError *error;
static alarmClockAlarmClock* source;
static GDBusConnection* connection;

void init(void)
{

    gchar *addr = g_dbus_address_get_for_bus_sync(G_BUS_TYPE_SYSTEM, NULL, &error);

    connection = g_dbus_connection_new_for_address_sync
                (
                addr,
                G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT|G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION,
                NULL,
                NULL,
                &error
                );
    source = alarm_clock_alarm_clock_proxy_new_sync
            (
                connection,
                G_DBUS_PROXY_FLAGS_NONE,
                name,
                path,
                NULL,
                &error
            );

}

cbool OnSignalRecieve(cbool (*Callback)(void))
{
    printf("Inside the Library\n");
    g_signal_connect(source,"ring-alarm",G_CALLBACK(Callback),&error);
    return TRUE;
}

cbool SetTime(const char* time)
{
    alarm_clock_alarm_clock_call_set_time_sync(source,time,NULL,&error);
    return TRUE;
}
cbool SetAlarmTime(const char* alarm)
{
    alarm_clock_alarm_clock_call_set_alarm_time_sync(source,alarm,NULL,&error);
    return TRUE;
}
cbool SetAlarmStatus(cbool status)
{
    alarm_clock_alarm_clock_call_set_alarm_status_sync(source,status,NULL,&error);
    return TRUE;
}
cbool GetAlarmStatus(cbool *result)
{
    printf("before\n");
    alarm_clock_alarm_clock_call_get_alarm_status_sync(source,result,NULL,&error);
    printf("check\n");
    return TRUE;
}
void deinit(void)
{
    //WIP
}
