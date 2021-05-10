/* Copyright (c) 2021, Alibaba Inc.
 * All rights reserved
 */

/* This header file is part of Alibaba RTC engine sdk for
 * iOS/Mac system.
 */

#import <Foundation/Foundation.h>

#define AliEngineDebugLog(format,...) [AliRtcLog log:AliRTCLogLevelINFO file:__FILE__ func:__FUNCTION__ line:__LINE__ tag:"AliRTCEngine" formatStr:format,##__VA_ARGS__];

#define AliEngineFatalLog(format,...) [AliRtcLog log:AliRTCLogLevelFATAL file:__FILE__ func:__FUNCTION__ line:__LINE__ tag:"AliRTCEngine" formatStr:format,##__VA_ARGS__];

typedef NS_ENUM(NSUInteger, AliRTCLogLevel) {
    AliRTCLogLevelDUMP,
    AliRTCLogLevelDEBUG,
    AliRTCLogLevelVERBOSE,
    AliRTCLogLevelINFO,
    AliRTCLogLevelWARNING,
    AliRTCLogLevelERROR,
    AliRTCLogLevelFATAL,
    AliRTCLogLevelNONE,
};


@interface AliRtcLog : NSObject

/**
 * 使用AliRTC 日志系统打印日志，不建议外部使用。
 */
+ (void)log:(AliRTCLogLevel)level
       file:(const char*)file
       func:(const char *)funct
       line:(int)line
        tag:(const char*)tag
  formatStr:(NSString *)format, ...;

@end
