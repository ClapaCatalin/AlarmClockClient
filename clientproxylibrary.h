#ifndef CLIENTPROXYLIBRARY_H
#define CLIENTPROXYLIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int cbool;
#define true 1
#define false 0

void init(void);
void uninit(void);

cbool OnSignalRecieve(cbool (*Callback)(void));

cbool SetTime(const char* time);
cbool SetAlarmTime(const char* alarm);
cbool SetAlarmStatus(cbool status);
cbool GetAlarmStatus(cbool *result);

#ifdef __cplusplus
}
#endif

#endif // CLIENTPROXYLIBRARY_H
