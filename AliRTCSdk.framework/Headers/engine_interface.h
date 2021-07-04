#ifndef engine_interface_h
#define engine_interface_h

#include <stdint.h>
#include <stdio.h>

#include "engine_define.h"
#include "engine_device_manager.h"
#include "engine_media_engine.h"
#include "engine_utils.h"

#define kAliRTCEngineDeviceMax 256
#define QUERY_INTERFACE(engine, type, interface) {if((engine)==NULL) {interface=NULL;} else {engine->QueryInterface(type, (void**)&interface);}}

namespace AliRTCSdk
{
    /**
     * @brief 功能接口类型
     */
    typedef enum {
      AliEngineInterfaceAudioDeviceManger = 0,
      AliEngineInterfaceVideoDeviceManger = 1,
      AliEngineInterfaceMediaEngine = 2,
    } AliEngineInterfaceIdType;

    /**
     * @brief 频道类型
     */
    typedef enum {
        AliEngineCommunication   = 0,
        AliEngineInteractiveLive,
        AliEngineInteractiveWithLowLatencyLive,
    } AliEngineChannelProfile;
    
    /**
     * @brief 用户角色
     */
    typedef enum {
        AliEngineClientRoleInteractive = 0,
        AliEngineClientRoleLive,
    } AliEngineClientRole;
    
    /**
     * @brief 网络状况
     */
    typedef enum {
        AliEngineNetworkQualityExcellent     = 0,
        AliEngineNetworkQualityGood          = 1,
        AliEngineNetworkQualityPoor          = 2,
        AliEngineNetworkQualityBad           = 3,
        AliEngineNetworkQualityVeryBad       = 4,
        AliEngineNetworkQualityDisconnect    = 5,
        AliEngineNetworkQualityUnknow        = 6,
    } AliEngineNetworkQuality;
    
    /**
     * @brief 视频窗口镜像模式
     */
    typedef enum {
        AliEngineRenderMirrorModeOnlyFrontMirror  = 0,
        AliEngineRenderMirrorModeAllMirror        = 1,
        AliEngineRenderMirrorModeAllNoMirror      = 2,
        AliEngineRenderMirrorModeNoChange         = 99,
    } AliEngineRenderMirrorMode;

    /**
     * @brief camera方向
     */
    typedef enum {
         AliEngineCameraDirectionInvalid = -1,
         AliEngineCameraDirectionBack = 0,
         AliEngineCameraDirectionFront = 1,
     }AliEngineCameraDirection;


    /**
     * @brief 采集偏好
     */
    typedef enum {
        AliEngineCaptureOutputPreferenceAuto = 0,
        /* 根据设置的publsh profile 分辨率和帧率，选择最接近的摄像头输出参数 */
        AliEngineCaptureOutputPreferencePerformance = 1,
        /* 选择较高的摄像头输出参数 */
        AliEngineCaptureOutputPreferencePreview = 2,
    }AliEngineCaptureOutputPreference;

    /**
     * @brief 视频宽高比
     */
    typedef enum  {
        /** 16 : 9 */
      AliEngineVideoScale_16_9 = 0,
        /** 4 : 3 */
      AliEngineVideoScale_4_3,
    }AliEngineVideoScale;

    /**
     * @brief 日志级别
     */
    typedef enum {
        AliEngineLogLevelInfo = 3,
        AliEngineLogLevelWarn,
        AliEngineLogLevelError,
        AliEngineLogLevelFatal,
        AliEngineLogLevelNone,
    } AliEngineLogLevel;

    /**
     * @brief 设备方向
     */
    typedef enum {
        AliEngineOrientationModePortrait        = 0,
        AliEngineOrientationModeLandscapeLeft,
        AliEngineOrientationModePortraitUpsideDown,
        AliEngineOrientationModeLandscapeRight,
        AliEngineOrientationModeAuto,
    } AliEngineOrientationMode;

    /**
     * @brief 本地静音模式
     */
    typedef enum {
        AliEngineMuteLocalAudioModeDefault        = 0,
        AliEngineMuteLocalAudioModeMuteAll,
        AliEngineMuteLocalAudioModeMuteOnlyMic,
    } AliEngineMuteLocalAudioMode;

#if (defined(__APPLE__) && TARGET_OS_IOS)
    /**
     * @brief AVAudioSession控制权限设置
     */
    typedef enum {
        AliEngineAudioSessionOperationRestrictionNone               = 0,
        AliEngineAudioSessionOperationRestrictionSetCategory,
        AliEngineAudioSessionOperationRestrictionConfigureSession,
        AliEngineAudioSessionOperationRestrictionDeactivateSession,
    } AliEngineAudioSessionOperationRestriction;
#endif

    /**
     * @brief 变声音效模式
     */
    typedef enum {
        AliEngineAudioEffectVoiceChangerOff = 0,     /* 关闭 */
        AliEngineAudioEffectVoiceChangerOldMan,      /* 老人 */
        AliEngineAudioEffectVoiceChangerBabyBoy,     /* 男孩 */
        AliEngineAudioEffectVoiceChangerBabGirl,     /* 女孩 */
        AliEngineAudioEffectVoiceChangerRobot,       /* 机器人 */
        AliEngineAudioEffectVoiceChangerDaimo,       /* 大魔王 */
        AliEngineAudioEffectVoiceChangerKTV,         /* KTV */
        AliEngineAudioEffectVoiceChangerEcho,        /* 回声 */
    } AliEngineAudioEffectVoiceChangerMode;
    
    /**
     * @brief 音效模式
     */
    typedef enum {
        AliEngineAudioEffectReverbOff             = 0,/* 关闭 */
        AliEngineAudioEffectReverbVocal_I,            /* 人声 I */
        AliEngineAudioEffectReverbVocal_II,           /* 人声 II */
        AliEngineAudioEffectReverbBathroom,           /* 澡堂 */
        AliEngineAudioEffectReverbSmallRoomBright,    /* 明亮小房间 */
        AliEngineAudioEffectReverbSmallRoomDark,      /* 黑暗小房间 */
        AliEngineAudioEffectReverbMediumRoom,         /* 中等房间 */
        AliEngineAudioEffectReverbLargeRoom,          /* 大房间 */
        AliEngineAudioEffectReverbChurchHall,         /* 教堂走廊 */
    } AliEngineAudioEffectReverbMode;

    /**
     * @brief 音效混响模式
     */
    typedef enum {
        AliEngineAudioEffectReverbRoomSize      = 0, /* 房间大小 [0, 100] */
        AliEngineAudioEffectReverbPreDelay,          /* 预延时ms [0, 200] */
        AliEngineAudioEffectReverbReverberance,      /* 混响感[0,100] */
        AliEngineAudioEffectReverbHfDamping,         /* 消声 [0,100] */
        AliEngineAudioEffectReverbToneLow,           /* 低音调[0,100] */
        AliEngineAudioEffectReverbToneHigh,          /* 高音调[0,100] */
        AliEngineAudioEffectReverbDryGain,           /* 干增益[-20,10] */
        AliEngineAudioEffectReverbWetGain,           /* 湿增益[-20,10] */
    } AliEngineAudioEffectReverbParamType;

    /**
     * @brief 录制类型
     */
    typedef enum {
        /** 录制单个音频文件 */
        AliEngineRecordTypeAudio   = 0,
        /** 录制单个音视频文件 */
        AliEngineRecordTypeVideo,
        /** 录制纯音频和音视频文件 */
        AliEngineRecordTypeBoth,
    } AliEngineRecordType;

    /**
     * @brief 录制格式
     */
    typedef enum {
        /** 录制AAC格式文件 */
        AliEngineRecordFormatAAC   = 0,
        /** 录制WAV格式文件 */
        AliEngineRecordFormatWAV,
        /** 录制MP4格式文件 */
        AliEngineRecordFormatMP4,
    } AliEngineRecordFormat;

    /**
     * @brief 录制音频质量
     */
    typedef enum {
        /** 低质量文件录制，文件体积较小，音质一般 */
        AliEngineAudioQualityLow       = 0,
        /** 中等质量文件录制，文件体积中等，音质中等 */
        AliEngineAudioQualityMidium,
        /** 高质量文件录制，文件体积较大，音质较好 */
        AliEngineAudioQualityHigh,
    } AliEngineAudioQuality;

    /**
     * @brief 录制视频质量
     */
    typedef enum {
        /** 录制默认质量视频, 和采集一致 */
        AliEngineVideoQualityDefault = 0,
    } AliEngineVideoQuality;

    /**
     * @brief 录制视频分辨率
     * @note 画布大小
     */
    typedef struct AliEngineVideoRecordCanvasConfig {
        /** 录制视频宽 */
        int canvasWidth;
        /** 录制视频高 */
        int canvasHeight;
    }AliEngineVideoRecordCanvasConfig;

    /**
     * @brief 录制视频背景色
     */
    typedef struct AliEngineRecordVideoBgColor {
        /** 红色分量 */
        unsigned char r;
        /** 绿色分量 */
        unsigned char g;
        /** 蓝色分量 */
        unsigned char b;
    }AliEngineRecordVideoBgColor;

    /**
     * @brief 录制视频坐标值
    */
    typedef struct AliEngineRecordVideoRational {
        unsigned int numerator;
        unsigned int denominator;
    }AliEngineRecordVideoRational;

    /**
    * @brief 录制视频布局
    */
    typedef enum {
        /** 网格布局 */
        AliEngineRecordVideoLayoutModeGrid = 0,
        /** 演讲者布局 */
        AliEngineRecordVideoLayoutModeSpeaker,
        /** 只有一个画面布局 */
        AliEngineRecordVideoLayoutModeUnique,
        /** 自定义布局 */
        AliEngineRecordVideoLayoutModeCustom,
    }AliEngineRecordVideoLayoutMode;

    /**
     * @brief 录制视频坐标
    */
    typedef struct AliEngineRecordVideoRectangle {
      AliEngineRecordVideoRational left;// percentage
      AliEngineRecordVideoRational top;
      AliEngineRecordVideoRational width;
      AliEngineRecordVideoRational height;
    }AliEngineRecordVideoRectangle;

    /**
     * @brief 录制视频用户布局
    */
    typedef struct AliEngineRecordVideoRegion {
      char* userId;
      AliEngineVideoSource sourceType;
      AliEngineRecordVideoRectangle area;
    }AliEngineRecordVideoRegion;

    /**
     * @brief 本地录制布局列表
     */
    class ALI_RTC_API AliEngineRecordVideoRegionArray
    {
    public:
      AliEngineRecordVideoRegionArray();
      virtual ~AliEngineRecordVideoRegionArray();
      AliEngineRecordVideoRegionArray(const AliEngineRecordVideoRegionArray &other);
      AliEngineRecordVideoRegionArray & operator=(const AliEngineRecordVideoRegionArray& other);

      void AddRecordVideoRegion(const AliEngineRecordVideoRegion &item);
      const AliEngineRecordVideoRegion &GetRecordVideoRegion(int index) const;
      void Clear();
      int Count() const;

    private:
      void *data_{ nullptr };
      AliEngineRecordVideoRegion emptyRegion_;
    };

    /**
     * @brief 录制视频布局
    */
    typedef struct AliEngineRecordVideoLayout {
        /** 视频布局模式 */
        AliEngineRecordVideoLayoutMode mode = AliEngineRecordVideoLayoutModeGrid;
        /** 录制视频用户布局数组 */
        AliEngineRecordVideoRegionArray shapes;
        /** 录制视频背景色 */
        AliEngineRecordVideoBgColor backColor = {0x00, 0x00, 0x00};
    }AliEngineRecordVideoLayout;

    /**
     * @brief 录制视频模板
    */
    typedef struct AliEngineRecordTemplate {
        /** 录制类型 */
        AliEngineRecordType recordType;
        /** 录制格式 */
        AliEngineRecordFormat recordFormat;
        /** 音频采样率类型 */
        AliEngineAudioSampleRate sampleRate = AliEngineAudioSampleRate_16000;
        /** 音频录制质量 */
        AliEngineAudioQuality audioQuality  = AliEngineAudioQualityHigh;
        /** 外部pcm采集 */
        bool externalPcmCaptureRecording    = false;
        /** 外部pcm渲染 */
        bool externalPcmRenderRecording     = true;
        /** 录制视频分辨率 */
        AliEngineVideoRecordCanvasConfig canvas;
        /** 分段录制 */ 
        bool isFragment                     = true;
        /** 帧率 */
        int fps                             = 15;
        /** 码率 */
        int bitrate                         = 500;
    }AliEngineRecordTemplate;

    /**
     * @brief OnBye返回类型
     */
    typedef enum {
        AliEngineOnByeBeKickOut            = 1,
        AliEngineOnByeChannelTerminated    = 2,
        AliEngineOnByeUserReplaced         = 3,
    } AliEngineOnByeType;

    /**
     * @brief SDK错误码
    */
    typedef enum {
      AliEngineErrorJoinBadAppId = 0x02010201,
      AliEngineErrorJoinInvaildAppId = 0x02010202,
      AliEngineErrorJoinBadChannel = 0x02010204,
      AliEngineErrorJoinInvaildChannel = 0x02010203,
      AliEngineErrorJoinBadToken = 0x02010205,
      AliEngineErrorJoinTimeout = 0x01020204,
      AliEngineErrorJoinBadParam = 0x01030101,
      AliEngineErrorJoinChannelFailed = 0x01030202,

      AliEngineErrorMicOpenFail = 0x01040404,
      AliEngineErrorSpeakerOpenFail = 0x01040405,
      AliEngineErrorMicInterrupt = 0x01040406,
      AliEngineErrorSpeakerInterrupt = 0x01040407,
      AliEngineErrorMicAuthFail = 0x01040408,
      AliEngineErrorMicNotAvailable = 0x01040409,
      AliEngineErrorSpeakerNotAvailable = 0x01040410,
      AliEngineErrorCameraOpenFail = 0x01040104,
      AliEngineErrorCameraInterrupt = 0x01040106,
      AliEngineErrorVideoDisplayOpenFail = 0x01040201,
      AliEngineErrorVideoDisplayInterrupt = 0x01040202,
      AliEngineErrorAudioBufferFull = 0x01070101,
      AliEngineErrorVideoBufferFull = 0x01070102,
      AliEngineErrorAudioStreamError = 0x01080101,
      AliEngineErrorAudioFileOpenFail = 0x01080102,
      AliEngineErrorAudioFormatNotSupported = 0x01080103,

      AliEngineErrorIceConnectionConnectFail = 0x01050201,
      AliEngineErrorIceConnectionReconnectFail = 0x01050202,
      AliEngineErrorIceConnectionHeartbeatTimeout = 0x0102020C,

      AliEngineErrorLowLatencyLiveCommunicationFail = 0x01070003,
      AliEngineErrorLowLatencyLiveMediaSettingFail = 0x01070004,
      AliEngineErrorLowLatencyLiveNoneBroadcaster = 0x01070005,
      AliEngineErrorLowLatencyLiveNeedRestart = 0x01070006,
      AliEngineErrorLowLatencyLiveNeedRestartAgainLater = 0x01070007,
      AliEngineErrorLowLatencyLiveServiceUnavailable = 0x01070008,
      AliEngineErrorLowLatencyLiveMediaConnectionInterrruption = 0x01070009,

      AliEngineErrorUpdateRoleChannel = 0x01070102,

      AliEngineErrorPublishInvaild = 0x01030305,
      AliEngineErrorPublishNotJoinChannel = 0x01010406,
      AliEngineErrorPublishAudioStreamFailed = 0x01010450,
      AliEngineErrorPublishVideoStreamFailed = 0x01010451,
      AliEngineErrorPublishDualStreamFailed = 0x01010452,
      AliEngineErrorPublishScreenShareFailed = 0x01010453,
      AliEngineErrorPublishScreenShareConfigError = 0x01010454,

      AliEngineErrorSubscribeInvaild = 0x01030404,
      AliEngineErrorSubscribeNotJoinChannel = 0x01010550,
      AliEngineErrorSubscribeAudioStreamFailed = 0x01010551,
      AliEngineErrorSubscribeVideoStreamFailed = 0x01010552,
      AliEngineErrorSubscribeDualStreamFailed = 0x01010553,
      AliEngineErrorSubscribeScreenShareFailed = 0x01010554,

      AliEngineErrorInvaildState = 0x01030204,
      AliEngineErrorSessionRemoved = 0x02010105,
      AliEngineErrorInvaildArgument = 0x01030103,
      AliEngineErrorInner = -1,
    }  AliEngineErrorCode;

    /**
     * SDK反馈问题类型
     */
    typedef enum {
        AliEngineFeedbackVideoDeviceFail   = 101,
        AliEngineFeedbackVideoNotRender    = 102,
        AliEngineFeedbackAudioDeviceFail   = 201,
        AliEngineFeedbackAudioNotRender    = 202,
        AliEngineFeedbackAudioEchoError    = 203,
        AliEngineFeedbackChannelTypeError  = 301,
        AliEngineFeedbackSDKTypeError      = 302,
        AliEngineFeedbackNetworkUnfluent   = 401,
        AliEngineFeedbackVideoBlurring     = 402,
        AliEngineFeedbackUnkonw            = -1,
    } AliEngineFeedbackType;

    /**
     * @brief 音乐伴奏播放状态
     */
    typedef enum {
        AliEngineAudioPlayingStarted        = 100,
        AliEngineAudioPlayingStopped        = 101,
        AliEngineAudioPlayingPaused         = 102,
        AliEngineAudioPlayingResumed        = 103,
        AliEngineAudioPlayingEnded          = 104,
        AliEngineAudioPlayingBuffering      = 105,
        AliEngineAudioPlayingBufferingEnd   = 106,
        AliEngineAudioPlayingFailed         = 107,
    } AliEngineAudioPlayingType;

    /**
     * @brief 音乐伴奏播放错误码
     */
    typedef enum {
        AliEngineAudioPlayingNoError   = 0,
        AliEngineAudioPlayingOpenFailed   = -100,
        AliEngineAudioPlayingDecodeFailed   = -101,
    } AliEngineAudioPlayingErrorCode;

    /**
     * @brief 网络连接状态
     */
    typedef enum {
        AliEngineConnectionInit = 0,       /* 初始化完成 */
        AliEngineConnectionDisconnected,   /* 网络连接断开 */
        AliEngineConnectionConnecting,     /* 建立网络连接中 */
        AliEngineConnectionConnected,      /* 网络已连接 */
        AliEngineConnectionReconnecting,   /* 重新建立网络连接中 */
        AliEngineConnectionFailed,         /* 网络连接失败 */
    } AliEngineConnectionStatus;

    /**
     * @brief 网络连接状态变更原因
    */
    typedef enum {
      AliEngineConnectionChangedDummyReason = 0,
      AliEngineConnectionMediaPathChanged,
      AliEngineConnectionSignalingHeartbeatTimeout,
      AliEngineConnectionSignalingHeartbeatAlive,
      AliEngineConnectionSignalingHttpdnsResolved,
      AliEngineConnectionSignalingHttpdnsFailure,
      AliEngineConnectionSignalingGslbFailure,
      AliEngineConnectionSignalingGslbSucccess,
      AliEngineConnectionSignalingJoinChannelFailure,
      AliEngineConnectionSignalingJoinChannelSuccess,
      AliEngineConnectionSignalingLeaveChannel,
      AliEngineConnectionSignalingConnecting,
    } AliEngineConnectionStatusChangeReason;

    /**
     * @brief 桌面分享类型
     */
    typedef enum {
      AliEngineScreenShareDesktop,      /* 桌面分享 */
      AliEngineScreenShareWindow,       /* 窗口分享 */
    } AliEngineScreenShareType;

    /**
     * @brief 外接设备类型
    */
    typedef enum {
      AliEngineExternalTypeUnknown = -1,       /* 未知类型 */
      AliEngineExternalTypeAudioCapture = 0,   /* 音频采集设备 */
      AliEngineExternalTypeAudioPlayout = 1,   /* 音频播放设备 */
      AliEngineExternalTypeVideoCapture = 2,   /* 视频采集设备 */
    }AliEngineExternalDeviceType;

    /**
     * @brief 外接设备状态
     */
    typedef enum {
      AliEngineExternalDeviceAdd = 0,      /* 新增外接设备 */
      AliEngineExternalDeviceRemove = 1,   /* 移除外接设备 */
    }AliEngineExternalDeviceState;

    /**
     * @brief 语音路由类型
    */
    typedef enum {
      AliEngineAudioRouteTypeDefault        = 0, /* 默认的语音路由 */
      AliEngineAudioRouteTypeHeadset        = 1, /* 耳机 */
      AliEngineAudioRouteTypeEarpiece       = 2, /* 听筒 */
      AliEngineAudioRouteTypeHeadsetNoMic   = 3, /* 不带麦的耳机 */
      AliEngineAudioRouteTypeSpeakerphone   = 4, /* 手机扬声器 */
      AliEngineAudioRouteTypeLoudSpeaker    = 5, /* 外接扬声器 */
      AliEngineAudioRouteTypeBlueTooth      = 6, /* 蓝牙耳机 */
      AliEngineAudioRouteTypeUSB            = 7, /* USB耳机 */
    }AliEngineAudioRouteType;

    /**
     * @brief 音频焦点类型
    */
    typedef enum {
      AliEngineAudioFocusNone                          = 0,
      AliEngineAudioFocusGain                          = 1,
      AliEngineAudioFocusGainTransient                 = 2,
      AliEngineAudioFocusGainTransientMayDuck          = 3,
      AliEngineAudioFocusGainTransientExclusive        = 4,
      AliEngineAudioFocusLoss                          = -1,
      AliEngineAudioFocusLossTransient                 = -2,
      AliEngineAudioFocusLossCanDuck                   = -3
    }AliEngineAudioFocusType;

    /**
     * @brief 推流状态
    */
    typedef enum {
      AliEngineStatsPublishIdle = 0,  /* 初始状态 */
      AliEngineStatsNoPublish = 1,    /* 未推流 */
      AliEngineStatsPublishing = 2,   /* 推流中 */
      AliEngineStatsPublished = 3,    /* 已推流 */
    } AliEnginePublishState;

    /**
     * @brief 订阅状态
    */
    typedef enum {
      AliEngineStatsSubscribeIdle = 0,  /* 初始状态 */
      AliEngineStatsNoSubscribe = 1,    /* 未订阅 */
      AliEngineStatsSubscribing = 2,    /* 订阅中 */
      AliEngineStatsSubscribed = 3,     /* 已订阅 */
    } AliEngineSubscribeState;

    /**
     * @brief 旁路推流错误码
    */
    typedef enum {
      AliEngineLiveTranscodingErrorPublishOk            = 0,
      AliEngineLiveTranscodingErrorStreamNotFound       = 0x01100001,
      AliEngineLiveTranscodingErrorStreamAlreadyExist   = 0x01100002,
      AliEngineLiveTranscodingErrorInvalidParam         = 0x01100003,
      AliEngineLiveTranscodingErrorInternalError        = 0x01100004,
      AliEngineLiveTranscodingErrorRtmpServerError      = 0x01100005,
      AliEngineLiveTranscodingErrorRtmpStreamUrlError   = 0x01100006,
      AliEngineLiveTranscodingErrorPublishTimeout       = 0x01100007,
      AliEngineLiveTranscodingErrorNotAuthorized        = 0x01100008,
    } AliEngineLiveTranscodingErrorCode;

    /**
     * @brief 旁路推流PublishTask状态
    */
    typedef enum {
      AliEngineTrascodingPublishTaskStatusStart = 0,                /* 任务开始 */
      AliEngineTrascodingPublishTaskStatusUpdate = 1,               /* 任务更新 */
      AliEngineTrascodingPublishTaskStatusStop = 2,                 /* 任务已停止 */
    } AliEngineTrascodingPublishTaskStatus;

    /**
     * @brief 用户离线原因
    */
    typedef enum {
      AliEngineUserOfflineQuit = 0,              /* 用户主动离开 */
      AliEngineUserOfflineDropped = 1,           /* 因过长时间收不到对方数据包，超时掉线 */
      AliEngineUserOfflineBecomeAudience = 2,    /* 用户身份从主播切换为观众时触发 */
    } AliEngineUserOfflineReason;

    /**
     * @brief 音频编码配置
    */
    typedef enum {
      AliEngineLowQualityMode = 0x0000,               /* 1ch, 8khz,  24kbps */
      AliEngineBasicQualityMode = 0x0001,             /* 1ch, 16khz, 24kbps */
      AliEngineHighQualityMode = 0x0010,              /* 1ch, 48khz, 48kbps */
      AliEngineStereoHighQualityMode = 0x0011,        /* 2ch, 48khz, 64kbps */
      AliEngineSuperHighQualityMode = 0x0012,         /* 1ch, 48khz, 96kbps */
      AliEngineStereoSuperHighQualityMode = 0x0013,   /* 2ch, 48khz, 128kbps */
    }AliEngineAudioProfile;

    /**
     * @brief 音频场景
    */
    typedef enum {
      AliEngineSceneDefaultMode = 0x0000,
      AliEngineSceneEducationMode = 0x0100,
      AliEngineSeneMediaMode = 0x0200,
      AliEngineSceneMusicMode = 0x0300,
      AliEngineSceneChatroomMode = 0x0400,
    }AliEngineAudioScenario;

    /**
     * @brief 跨频道转发状态
    */
    typedef enum {
        AliEngineChannelRelayEventStart = 0,
        AliEngineChannelRelayEventUpdate,
        AliEngineChannelRelayEventStop,
    } AliEngineChannelRelayEvent;

    /**
     * @brief 跨频道转发状态
    */
    typedef enum {
        AliEngineChannelRelayStateInit = 3,
        AliEngineChannelRelayStateConnecting,
        AliEngineChannelRelayStateRunning,
        AliEngineChannelRelayStateFailure,
    } AliEngineChannelRelayState;

    /**
     * @brief 跨频道转发错误码
    */
    typedef enum {
        AliEngineChannelRelayErrorStateError = 0x01200001,       /*检测到本地状态不对，没入会，角色错误，频道模式错误 */
        AliEngineChannelRelayErrorSrcNotAllow = 0x01200002,      /*服务端返回436，源通道模式不匹配 */
        AliEngineChannelRelayErrorJoinDestFailed = 0x01200003,   /*服务端返回437，目标通道不存在或者模式不匹配 */
        AliEngineChannelRelayErrorTokenInvalid = 0x01200004,     /*服务端返回438，token无效 */
        AliEngineChannelRelayErrorRoleError = 0x01200005,        /*服务端返651，session不是主播 */
        AliEngineChannelRelayErrorInvalidParam = 0x01200006,     /*服务端400，参数错误 */
        AliEngineChannelRelayErrorToSelf = 0x01200007,           /*服务端返回440，不能转推到本频道 */
    } AliEngineChannelRelayErrorCode;

    /**
     * @brief 用户离线原因
    */
    typedef enum {
      AliEngineShowTypeNone = 0,              /* 不显示 */
      AliEngineShowTypeAudio = 1,             /* 音频 */
      AliEngineShowTypeVideo = 2,             /* 视频 */
      AliEngineShowTypeNetwork = 3,           /* 网络 */
      AliEngineShowTypeAll = 4,               /* 全部 */
    } AliEngineShowDebugViewType;


    /**
     * @brief 屏幕分享区域
     */
    typedef struct AliEngineScreenShareRegion {
      float originX = -1.f;
      float originY = -1.f;
      float width = 0.f;
      float height = 0.f;
    } AliEngineScreenShareRegion;

    /**
     * @brief 屏幕分享源信息
     */
    typedef struct AliEngineScreenSourcInfo {
        String sourceId;
        String sourceName;
    } AliEngineScreenSourcInfo;

    /**
     * @brief 屏幕分享源列表
     */
    class ALI_RTC_API AliEngineScreenSourceList {
    public:
        virtual unsigned int GetCount() = 0;
        virtual AliEngineScreenSourcInfo GetSourceInfo(unsigned int index) = 0;
        virtual void Release() = 0;
    };

    /**
     * @brief 用户鉴权信息
     */
    typedef struct AliEngineAuthInfo {
        char* channelId     = nullptr;
        char* userId        = nullptr;
        char* appId         = nullptr;
        char* nonce         = nullptr;
        char* token         = nullptr;
        char* role          = nullptr;
        char* session  = nullptr;
        char** gslb    = nullptr;
        int gslbCount  = 0;
        char** agent   = nullptr;
        int agentCount = 0;
        unsigned long long timestamp =0;
        char* tokenType    = nullptr;
    } AliEngineAuthInfo;

    /**
     * @brief 用户鉴权信息列表
     */
    typedef struct _tagAliEngineAuthInfoList {
        _tagAliEngineAuthInfoList(int size) {
            if (size>0)
            {
                count = size;
                infoList = new AliEngineAuthInfo[count];
            }
        };

        ~_tagAliEngineAuthInfoList() {
            if (infoList)
            {
                delete[] infoList;
                infoList = nullptr;
                count = 0;
            }
        };
        AliEngineAuthInfo* infoList = nullptr;
        int count = 0;
    }AliEngineAuthInfoList;

    /**
     * @brief camera 采集偏好
     */
    typedef struct AliEngineCameraCapturerConfiguration {
        AliEngineCaptureOutputPreference preference;        /** Camera capturer preference settings. See: #AliEngineCaptureOutputPreference. */
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
        AliEngineCameraDirection cameraDirection;           /** Camera direction settings (for Android/iOS only). See: #AliEngineCameraDirection. */
#endif
    } AliEngineCameraCapturerConfiguration;

    /**
     * @brief 视频帧率
     */
    enum AliEngineFrameRate {
        /** 5: 5 fps */
        AliEngineFrameRateFps5 = 5,
        /** 10: 10 fps */
        AliEngineFrameRateFps10 = 10,
        /** 15: 15 fps */
        AliEngineFrameRateFps15 = 15,
        /** 20: 20 fps */
        AliEngineFrameRateFps20 = 20,
        /** 25: 25 fps */
        AliEngineFrameRateFps25 = 25,
        /** 30: 30 fps */
        AliEngineFrameRateFps30 = 30,
    };

    /**
     * @brief 视频编码码率
     */
    enum AliEngineVideoEncoderBitrate {
        AliEngineVideoStandardBitrate = 0,
    };

    /**
     * @brief 视频输出模式
     */
    enum AliEngineVideoEncoderOrientationMode {
      /** 0: (Default) Adaptive mode.
       */
        AliEngineVideoEncoderOrientationModeAdaptive = 0,
        /** 1: Landscape mode.

         The video encoder always sends the video in landscape mode. The video encoder rotates the original video before sending it and the rotational infomation is 0. This mode applies to scenarios involving CDN live streaming.
         */
        AliEngineVideoEncoderOrientationModeFixedLandscape = 1,
        /** 2: Portrait mode.

         The video encoder always sends the video in portrait mode. The video encoder rotates the original video before sending it and the rotational infomation is 0. This mode applies to scenarios involving CDN live streaming.
         */
        AliEngineVideoEncoderOrientationModeFixedPortrait = 2,
    };

    /**
     * @brief 视频镜像模式
     */
    enum AliEngineVideoMirrorMode
    {
        /** 0: (Default) disable the mirror mode.
        */
        AliEngineVideoMirrorModeDisabled = 0,//disable mirror
        /** 1: Enable mirror mode. */
        AliEngineVideoMirrorModeEnable = 1,//enabled mirror
    };

    /**
     * @brief 视频分辨率
     */
    struct AliEngineVideoDimensions {
        /** Width (pixels) of the video. */
        int width;
          /** Height (pixels) of the video. */
        int height;
        AliEngineVideoDimensions()
            : width(640), height(480)
        {}
        AliEngineVideoDimensions(int w, int h)
            : width(w), height(h)
        {}
    };

    /**
     * @brief 视频编码属性设置
     */
    struct AliEngineVideoEncoderConfiguration{
        AliEngineVideoDimensions dimensions;
        AliEngineFrameRate frameRate;
        int bitrate;
        AliEngineVideoEncoderOrientationMode orientationMode;
        AliEngineVideoMirrorMode mirrorMode;
        AliEngineRotationMode rotationMode;
        
        AliEngineVideoEncoderConfiguration(
            const AliEngineVideoDimensions& d, AliEngineFrameRate f,
            int b, AliEngineVideoEncoderOrientationMode m, AliEngineVideoMirrorMode mr = AliEngineVideoMirrorModeDisabled, AliEngineRotationMode rotation = AliEngineRotationMode_0)
            : dimensions(d), frameRate(f), bitrate(b),
              orientationMode(m), mirrorMode(mr), rotationMode(rotation)
        {}
        AliEngineVideoEncoderConfiguration(
            int width, int height, AliEngineFrameRate f,
            int b, AliEngineVideoEncoderOrientationMode m, AliEngineVideoMirrorMode mr = AliEngineVideoMirrorModeDisabled, AliEngineRotationMode rotation = AliEngineRotationMode_0)
            : dimensions(width, height), frameRate(f),
             bitrate(b), orientationMode(m), mirrorMode(mr), rotationMode(rotation)
        {}
        AliEngineVideoEncoderConfiguration()
            : dimensions(640, 480)
            , frameRate(AliEngineFrameRateFps15)
            , bitrate(512)
            , orientationMode(AliEngineVideoEncoderOrientationModeAdaptive)
            , mirrorMode(AliEngineVideoMirrorModeDisabled)
            , rotationMode(AliEngineRotationMode_0)
        {}
    };

    /**
     * @brief 屏幕流码属性设置
     */
    struct AliEngineScreenShareEncoderConfiguration{
        AliEngineVideoDimensions dimensions;
        AliEngineFrameRate frameRate;
        int bitrate;
        AliEngineRotationMode rotationMode;
        
        AliEngineScreenShareEncoderConfiguration(
            const AliEngineVideoDimensions& d, AliEngineFrameRate f,
            int b, AliEngineRotationMode rotation)
            : dimensions(d), frameRate(f), bitrate(b), rotationMode(rotation)
        {}
        AliEngineScreenShareEncoderConfiguration(
            int width, int height, AliEngineFrameRate f,
            int b, AliEngineRotationMode rotation)
            : dimensions(width, height), frameRate(f),
             bitrate(b), rotationMode(rotation)
        {}
        AliEngineScreenShareEncoderConfiguration()
            : dimensions(0, 0)
            , frameRate(AliEngineFrameRateFps5)
            , bitrate(512)
            , rotationMode(AliEngineRotationMode_0)
        {}
    };

    /**
     * @brief 视频显示窗口设置
     */
    typedef struct AliEngineVideoCanvas {
        /** 显示视图 */
        void *displayView   = nullptr;
        /** 背景颜色，格式为RGB的Hex */
        int backgroundColor = 0;
        /** 渲染模式，默认值为{@link AliRTCSdk::AliEngineRenderModeAuto} */
        AliEngineRenderMode renderMode = AliEngineRenderMode::AliEngineRenderModeAuto;
        /** 镜像模式，默认值为{@link AliRTCSdk::AliEngineRenderMirrorModeOnlyFrontMirror} */
        AliEngineRenderMirrorMode mirrorMode = AliEngineRenderMirrorModeOnlyFrontMirror;
        /** 视频宽高比，默认值为 {@link AliRTCSdk::AliEngineVideoScale_16_9} */
        AliEngineVideoScale scaleMode = AliEngineVideoScale_16_9;
        /** 旋转角度，默认值为 {@link AliRTCSdk::AliEngineRotationMode_0} */
        AliEngineRotationMode rotation = AliEngineRotationMode_0;
        /** 支持第三方OpenGL ES纹理显示，纹理ID */
        long long renderId = 0;
        /** 支持第三方OpenGL ES纹理显示，纹理宽 */
        int width = 0;
        /** 支持第三方OpenGL ES纹理显示，纹理高 */
        int height = 0;
        /** 该参数只在iOS和Mac平台生效，
         * - true : 使用OpenGL ES 渲染
         * - false : 使用Metal渲染
         */
        bool enableGL = true;
    } AliEngineVideoCanvas;

    /**
     * @brief 录制音频设置
     */
    typedef struct AliEngineRecordAudioConfig {
        /** 音频采样率类型 */
        AliEngineAudioSampleRate sampleRate = AliEngineAudioSampleRate_16000;
        /** 音频录制质量 */
        AliEngineAudioQuality quality       = AliEngineAudioQualityHigh;
        /** 是否允许录制外部pcm输入采集数据 */
        bool externalPcmCaptureRecording    = false;
        /** 是否允许录制外部pcm输入渲染数据 */
        bool externalPcmRenderRecording     = true;
    } AliEngineRecordAudioConfig;

    /**
     * @brief 录制视频设置
     */
    typedef struct AliEngineRecordVideoConfig {
        /** 帧率 */
        int fps;
        /** 码率 */
        int bitrate;
        /** 视频录制质量 */
        AliEngineVideoQuality quality;
        /** 录制视频数据源 */
        AliEngineVideoRecordSource sourceType;
        /** 视频录制分辨率设置 */
        AliEngineVideoRecordCanvasConfig canvas;
    } AliEngineRecordVideoConfig;

    /**
     * @brief 音量信息
     */
    typedef struct AliEngineUserVolumeInfo {
        String uid = nullptr;  /* 用户id */
        bool speechState = 0;  /* 语音状态，1表示当前在说话，0表示当前未说话 */
        int volume = 0;        /* 音量 */
        int sumVolume = 0;    /* 回调周期内累计的音量, 用于判别当前说话人 */
    } AliEngineUserVolumeInfo;

    /**
     * @brief 会话数据统计信息
     */
    typedef struct AliEngineStats {
        long long availableSendBitrate = 0;
        long long sentKBitrate = 0;
        long long rcvdKBitrate = 0;
        long long sentBytes = 0;
        long long rcvdBytes = 0;
        long long videoRcvdKBitrate = 0;
        long long videoSentKBitrate = 0;
        unsigned int systemCpu = 0;
        unsigned int appCpu = 0;
        unsigned long long callDuration = 0;
        long long sentLossRate = 0;
        long long sentLossPkts = 0;
        long long sentExpectedPkts = 0;
        long long rcvdLossRate = 0;
        long long rcvdLossPkts = 0;
        long long rcvdExpectedPkts = 0;
        long long lastmileDelay = 0;
    } AliEngineStats;

    /**
     * @brief 本地视频统计信息
     */
    typedef struct AliEngineLocalVideoStats {
        AliEngineVideoTrack track;
        unsigned int targetEncodeBitrate = 0;
        unsigned int actualEncodeBitrate = 0;
        unsigned int sentBitrate = 0;
        unsigned int sentFps = 0;
        unsigned int encodeFps = 0;
        unsigned int captureFps = 0;
        unsigned int avgQpPerSec = 0;
    } AliEngineLocalVideoStats;

    /**
     * @brief 远端视频统计信息
     */
    typedef struct AliEngineRemoteVideoStats {
        const char* userId;
        AliEngineVideoTrack track;
        unsigned int width = 0;
        unsigned int height = 0;
        unsigned int decodeFps = 0;
        unsigned int renderFps = 0;
        unsigned int frozenTimes = 0;
    } AliEngineRemoteVideoStats;

    /**
     * @brief 本地音频统计信息
     */
    typedef struct AliEngineLocalAudioStats {
        AliEngineAudioTrack track;
        unsigned int sentBitrate = 0;
        unsigned int sentSamplerate = 0;
        unsigned int numChannel = 0;
        unsigned int inputLevel = 0;
    } AliEngineLocalAudioStats;

    /**
     * @brief 远端音频统计信息
     */
    typedef struct AliEngineRemoteAudioStats {
        const char* userId;
        AliEngineAudioTrack track;
        int quality = 0;
        int networkTransportDelay = 0;
        int jitterBufferDelay = 0;
        int audioLossRate = 0;
        int rcvdBitrate = 0;
        int totalFrozenTimes = 0;
    } AliEngineRemoteAudioStats;
        
    /**
     * @brief 美颜参数
     */
    typedef struct AliEngineBeautyConfig {
        /** 美白等级，建议取值范围[0 - 1.0]  */
        float whiteningLevel;
        /** 磨皮等级，建议取值范围[0 - 1.0] */
        float smoothnessLevel;
    } AliEngineBeautyConfig;

    /**
     * @brief 水印坐标系
     */
    typedef struct AliEngineWaterMarkPosition {
        float x = 0;
        float y = 0;
        float w = 0;
        float h = 0;
    } AliEngineWaterMarkPosition;

    /**
     * @brief 水印配置
     */
    typedef struct AliEngineWaterMarkConfig {
        /** 预览水印是否可见  */
        bool visibleInPreview = true;
        /** 竖屏水印坐标信息  */
        AliEngineWaterMarkPosition positionInPortraitMode;
        /** 横屏水印坐标信息  */
        AliEngineWaterMarkPosition positionInLandscapeMode;
        /** 水印透明度  */
        float alpha = 1.0;
        /** 归一化  */
        bool normalized = false;
    } AliEngineWaterMarkConfig;

    /**
     * @brief 屏幕共享参数配置
     */
    typedef struct AliEngineScreenShareConfig {
        bool isShareByRegion = false;
        AliEngineScreenShareRegion shareRegion;

        void clear()
        {
            shareRegion.originX = -1.f;
            shareRegion.originY = -1.f;
            shareRegion.width = 0.f;
            shareRegion.height = 0.f;
        }
    } AliEngineScreenShareConfig;

    /**
     * @brief 屏幕共享配置信息
    */
    typedef struct AliEngineScreenShareInfo {
      AliEngineScreenShareType shareType = AliEngineScreenShareDesktop;
      unsigned int shareSourceId = 0;
      AliEngineScreenShareConfig shareConfig;
    } AliEngineScreenShareInfo;

    /**
     * @brief 消息通道消息
     * @note 已废弃使用
     */
    typedef struct AliEngineMessage {
        String tID;
        String contentType;
        String content;
    } AliEngineMessage;

    /**
     * @brief 消息通道Response
     * @note 已废弃使用
     */
    typedef struct AliEngineMessageResponse {
        int result;
        String contentType;
        String content;
    } AliEngineMessageResponse;

    /**
     * @brief 跨频道转推设置
     */
    struct AliEngineChannelRelayConfiguration {
      AliEngineChannelRelayConfiguration(int size) {
            if (size > 0)
            {
                destsSize = size;
                dests = new AliEngineAuthInfo[destsSize];
            }
        };

        ~AliEngineChannelRelayConfiguration() {
            if (dests)
            {
                delete[] dests;
                dests = nullptr;
                destsSize = 0;
            }
        };
        AliEngineAuthInfo* dests = nullptr;
        int destsSize = 0;
    };

    /** 旁路直播 **/
    enum AliEngineLiveTranscodingState {
        AliEngineLiveTranscodingState_IDLE = 0,
        AliEngineLiveTranscodingState_CONNNECT = 1,
        AliEngineLiveTranscodingState_RUNNING = 2,
        AliEngineLiveTranscodingState_RECOVERING = 3,
        AliEngineLiveTranscodingState_FAILURE = 4,
        AliEngineLiveTranscodingState_END = 5
    };

    /**
    * @brief 旁路模式
    */
    enum AliEngineLiveTranscodingMixMode {
        /** 单路模式 */
        AliEngineLiveTranscodingSINGLE = 0,  
        /** 混流模式 */
        AliEngineLiveTranscodingMIX = 1      
    };

    /**
    * @brief 旁路直播转推流模式
    */
    enum AliEngineLiveTranscodingStreamType {
        /** 原始流 */
        AliEngineLiveTranscodingOrigin = 0,
        /** 音频 */
        AliEngineLiveTranscodingAudio = 1,
        /** 视频 */
        AliEngineLiveTranscodingVideo = 2
    };

    /**
    * @brief 旁路直播输入类型
    */
    enum AliEngineLiveTranscodingSourceType {
        /** 相机流 */
        AliEngineLiveTranscodingCamera = 0,
        /** 屏幕流 */
        AliEngineLiveTranscodingShareScreen = 1
    };

    /**
    * @brief 旁路直播计费规格
    */
    enum AliEngineLiveTranscodingTaskProfile {
        AliEngineLiveTranscoding_Profile_1IN_1080P = 0,
        AliEngineLiveTranscoding_Profile_1IN_720P = 1,
        AliEngineLiveTranscoding_Profile_1IN_360P = 2,
        AliEngineLiveTranscoding_Profile_2IN_1080P = 3,
        AliEngineLiveTranscoding_Profile_2IN_720P = 4,
        AliEngineLiveTranscoding_Profile_2IN_360P = 5,
        AliEngineLiveTranscoding_Profile_4IN_1080P = 6,
        AliEngineLiveTranscoding_Profile_4IN_720P = 7,
        AliEngineLiveTranscoding_Profile_4IN_360P = 8,
        AliEngineLiveTranscoding_Profile_9IN_1080P = 9,
        AliEngineLiveTranscoding_Profile_9IN_720P = 10,
        AliEngineLiveTranscoding_Profile_9IN_360P = 11,
        AliEngineLiveTranscoding_Profile_12IN_1080P = 12,
        AliEngineLiveTranscoding_Profile_12IN_720P = 13,
        AliEngineLiveTranscoding_Profile_12IN_360P = 14,
        AliEngineLiveTranscoding_Profile_16IN_1080P = 15,
        AliEngineLiveTranscoding_Profile_16IN_720P = 16,
        AliEngineLiveTranscoding_Profile_16IN_360P = 17,
        AliEngineLiveTranscoding_Profile_Mixed = 9999 // only audio
    };

    /**
    * @brief 旁路直播音频采样
    */
    enum AliEngineLiveTranscodingAudioSampleRate {
        AliEngineLiveTranscoding_HZ_48000 = 48000,
        AliEngineLiveTranscoding_HZ_44100 = 44100,
        AliEngineLiveTranscoding_HZ_32000 = 32000,
        AliEngineLiveTranscoding_HZ_16000 = 16000,
        AliEngineLiveTranscoding_HZ_8000 = 8000
    };

    /**
    * @brief 旁路直播自定义编码参数
    */
    struct AliEngineLiveTranscodingEncodeParam {
        int videoWidth = 360; //(0-1920]
        int videoHeight = 640; //(0-1920]
        int videoFramerate = 15; //[1,60]
        int videoBitrate = 500; //[1kbps,10000kbps]
        int videoGop = 30; //[1,60]
        AliEngineLiveTranscodingAudioSampleRate audioSamplerate = AliEngineLiveTranscoding_HZ_32000;
        int audioBitrate = 500; //[8kbps,500kbps]
        int audioChannels = 1; //[1,2]
    };

    /**
    * @brief 旁路直播图片
    */
    struct AliEngineLiveTranscodingImage {
        enum DisplayType { NOT_DISPLAY = 0, ALWAYS = 1, WHEN_NO_VIDEO = 2 };

        String url;
        float alpha = 1.0;
        DisplayType display = DisplayType::ALWAYS;
        int x;
        int y;
        int width;
        int height;
        int zOrder = 0;
    };

    /**
     * @brief 旁路直播图片列表
     */
    class ALI_RTC_API AliEngineLiveTranscodingImageArray
    {
    public:
      AliEngineLiveTranscodingImageArray();
      virtual ~AliEngineLiveTranscodingImageArray();
      AliEngineLiveTranscodingImageArray(const AliEngineLiveTranscodingImageArray &other);
      AliEngineLiveTranscodingImageArray & operator=(const AliEngineLiveTranscodingImageArray& other);

      void Add(const AliEngineLiveTranscodingImage &item);
      AliEngineLiveTranscodingImage Get(int index) const;
      void Clear();
      int Count() const;

    private:
      void *data{ nullptr };
    };

    enum AliEngineLiveTranscodingFontType {
      NOTO_SERIF_CJKSC_REGULAR = 0,
      ALIBABA_PUHUITI_REGULAR = 1,
      ALIBABA_PUHUITI_BOLD = 2,
      ALIBABA_PUHUITI_Heavy = 3,
      ALIBABA_PUHUITI_LIGHT = 4,
      ALIBABA_PUHUITI_MEDIUM = 5
    };

    /**
    * @brief 旁路直播时钟格式
    */
    struct AliEngineLiveTranscodingClockWidget {
        int x;
        int y;
        AliEngineLiveTranscodingFontType fontType = NOTO_SERIF_CJKSC_REGULAR;
        int fontSize;
        int fontColor = 0xFFFFFF;  // 0xRRGGBB
        int zOrder = 0;
    };

    /**
     * @brief 旁路直播时钟格式列表
     */
    class ALI_RTC_API AliEngineLiveTranscodingClockWidgetArray
    {
    public:
      AliEngineLiveTranscodingClockWidgetArray();
      virtual ~AliEngineLiveTranscodingClockWidgetArray();
      AliEngineLiveTranscodingClockWidgetArray(const AliEngineLiveTranscodingClockWidgetArray &other);
      AliEngineLiveTranscodingClockWidgetArray & operator=(const AliEngineLiveTranscodingClockWidgetArray& other);

      void Add(const AliEngineLiveTranscodingClockWidget &item);
      AliEngineLiveTranscodingClockWidget Get(int index) const;
      void Clear();
      int Count() const;

    private:
      void *data{ nullptr };
    };

    /**
    * @brief 旁路直播文字格式
    */
    struct AliEngineLiveTranscodingText {
        String text;
        int x;
        int y;
        int zOrder;
        AliEngineLiveTranscodingFontType fontType = NOTO_SERIF_CJKSC_REGULAR;
        int fontSize;
        int fontColor = 0x000000;
    };

    /**
     * @brief 旁路直播文字列表
     */
    class ALI_RTC_API AliEngineLiveTranscodingTextArray
    {
    public:
      AliEngineLiveTranscodingTextArray();
      virtual ~AliEngineLiveTranscodingTextArray();
      AliEngineLiveTranscodingTextArray(const AliEngineLiveTranscodingTextArray &other);
      AliEngineLiveTranscodingTextArray & operator=(const AliEngineLiveTranscodingTextArray& other);

      void Add(const AliEngineLiveTranscodingText &item);
      AliEngineLiveTranscodingText Get(int index) const;
      void Clear();
      int Count() const;

    private:
      void *data{ nullptr };
    };

    /**
    * @brief 旁路直播裁剪模式
    */
    enum AliEngineLiveTranscodingCropMode {
        /** 剪裁 */
        AliEngineLiveTranscodingCrop = 1,
        /** 填充 */
        AliEngineLiveTranscodingFill = 2
    };

    /**
    * @brief 旁路直播媒体处理模式
    */
    enum AliEngineLiveTranscodingMediaProcessMode {
        /** 通用模式 */
        AliEngineLiveTranscodingNormal = 0, 
        /** 虚拟背景模式 */
        AliEngineLiveTranscodingVirtualBackground = 1 
    };

    /**
    * @brief 旁路直播输入类型
    */
    enum AliEngineLiveTranscodingSegmentType {
        /** 无人像分割 */
        AliEngineLiveTranscodingNoBody = 0,
        /** 人像分割 */ 
        AliEngineLiveTranscodingBody = 1    
    };

    /**
     * @brief 旁路直播用户信息
     */
    struct AliEngineLiveTranscodingUser{
        String userId;
        int x;
        int y;
        int width;
        int height;
        int zOrder;
        AliEngineLiveTranscodingSourceType sourceType;
        AliEngineLiveTranscodingSegmentType segmentType = AliEngineLiveTranscodingNoBody;
        AliEngineLiveTranscodingImageArray images;
        AliEngineLiveTranscodingTextArray texts;

        bool operator==(const AliEngineLiveTranscodingUser &rhs) const
        {
          return this->userId == rhs.userId;
        };
    };

    /**
     * @brief 旁路直播用户列表
    */
    class ALI_RTC_API AliEngineLiveTranscodingUserArray
    {
    public:
      AliEngineLiveTranscodingUserArray();
      virtual ~AliEngineLiveTranscodingUserArray();
      AliEngineLiveTranscodingUserArray(const AliEngineLiveTranscodingUserArray &other);
      AliEngineLiveTranscodingUserArray & operator=(const AliEngineLiveTranscodingUserArray& other);

      void AddTranscodingUser(const AliEngineLiveTranscodingUser &item);
      void RemoveTranscodingUser(const AliEngineLiveTranscodingUser &item);
      AliEngineLiveTranscodingUser GetTranscodingUser(int index) const;
      void Clear();
      int Count() const;

    private:
      void *data;
    };

    /**
    * @brief 旁路模式单路参数
    */
    struct AliEngineLiveTranscodingSingleParam
    {
        /** 用户id */
        String userId;
        /** 推流模式 */
        AliEngineLiveTranscodingStreamType streamType;
        /** 旁路直播输入类型 */
        AliEngineLiveTranscodingSourceType sourceType;
    };

    /**
    * @brief 旁路模式混流参数
    */
    struct AliEngineLiveTranscodingMixParam
    {
        /** 旁路直播计费规格 */
        AliEngineLiveTranscodingTaskProfile taskProfile;
        /** 旁路直播自定义编码参数 */
        AliEngineLiveTranscodingEncodeParam encodeParam;
        /** 旁路直播用户列表 */
        AliEngineLiveTranscodingUserArray users;
        /** 背景色 */
        int backgroundColor = 0x000000; //0xRRGGBB
        /** 背景图片列表 */
        AliEngineLiveTranscodingImageArray backgrounds;
        /** 水印列表 */
        AliEngineLiveTranscodingImageArray watermarks;
        /** 时钟组件列表 */
        AliEngineLiveTranscodingClockWidgetArray clockWidgets;
        /** 剪裁模式 */
        AliEngineLiveTranscodingCropMode cropMode;
        /** 媒体处理模式 */
        AliEngineLiveTranscodingMediaProcessMode mediaProcessMode;
    };

    /**
    * @brief 旁路模式参数
    */
    struct AliEngineLiveTranscodingParam
    {
        /** 旁路模式 */
        AliEngineLiveTranscodingMixMode mixMode = AliEngineLiveTranscodingMIX;
        /** 路模式单路参数 */
        AliEngineLiveTranscodingSingleParam singleParam;
        /** 旁路模式混流参数 */
        AliEngineLiveTranscodingMixParam mixParam;
    };

    /**
     * @brief 滑动配置
     * @note 已废弃使用
     */
    typedef struct AliEngineScrollViewConfig {
      float fOriginX;
      float fOriginY;
      float width;
      float height;
      AliEngineRenderMode renderMode{ AliEngineRenderModeAuto };
      AliEngineVideoTrack videoTrack{ AliEngineVideoTrackScreen };
    } AliEngineScrollViewConfig;

    /**
     * @brief 视频流的状态
     */
    typedef enum {
      AliEngineVideoClose = 0,
      AliEngineVideoOpen = 1,
    } AliEngineVideoState;


    /**
     * @brief 触发视频流状态变化的原因
     */
    typedef enum {
      AliEngineVideoChangeByClient = 0,
      AliEngineVideoChangeByServer = 1,
    } AliEngineVideoReason;

    /*
     * @brief 虚拟背景背景图缩放模式
     */
    typedef enum {
        AliEngineBokehScaleModelCrop = 0, /* 等比裁剪 */
        AliEngineBokehScaleModelFill = 1, /* 填充黑边 */
    }AliEngineBokehScaleModel;

    /**
     * @brief Qos反馈外置编码器请求帧类型
     */ 
    typedef enum {
        AliEngineVideoEncodedFrameNULL, /* 默认 无 */
        AliEngineVideoEncodedFrameIDR,  /* IDR帧  */
        AliEngineVideoEncodedFrameLTR,  /* LTR帧  */
        AliEngineVideoEncodedFrameB,    /* B帧  */
    } AliEngineVideoEncodedFrameType;

    /**
     * @brief Qos反馈外置编码器参数结构体
     * 
     */ 
    typedef struct AliEngineVideoExternalEncoderParameter{
        AliEngineVideoExternalEncoderParameter():
        width(0),
        height(0),
        frame_rate(0),
        bitrate_bps(0){}

        int32_t width;
        int32_t height;
        int32_t frame_rate;
        uint32_t bitrate_bps;
    }AliEngineVideoExternalEncoderParameter;    

    /**
     * @brief SDK事件回调基础类
     */
    class ALI_RTC_API AliEngineEventListener {
    public:
        
        virtual ~AliEngineEventListener() = default;

        /**
         * @brief 加入频道结果
         * @param result 加入频道结果，成功返回0，失败返回错误码
         * @param channel 频道id.
         * @param userId  用户userId
         * @note 已废弃
         */
        virtual void OnJoinChannelResult(int result, const char *channel, int elapsed) {}
        
        /**
         * @brief 加入频道结果
         * @details 当应用调用 {@link AliEngine::JoinChannel} 方法时，该回调表示成功/失败加入频道，并且返回频道加入的相关信息以及加入频道耗时
         * @param result 加入频道结果，成功返回0，失败返回错误码
         * @param channel 频道id.
         * @param userId  用户userId
         * @param elapsed 加入频道耗时
         */
        virtual void OnJoinChannelResult(int result, const char *channel, const char *userId, int elapsed) {}

        /**
         * @brief 离开频道结果
         * @details 应用调用 {@link AliEngine::LeaveChannel} 方法时，该回调表示成功/失败离开频道，回调将会返回离会的result和该频道的基本信息,如果 {@link AliEngine::LeaveChannel} 后直接 {@link AliEngine::Destory} SDK，将不会收到此回调
         * @param result 离开频道结果，成功返回0，失败返回错误码
         * @param stats 本次频道内会话的数据统计汇总。
         */
        virtual void OnLeaveChannelResult(int result, AliEngineStats stats) {}
        
        /**
         * @brief 当远端用户上线时会返回这个消息
         * @param uid User ID，从App server分配的唯一标示符
         * @param elapsed 用户加入频道时的耗时
         */
        virtual void OnRemoteUserOnLineNotify(const char *uid, int elapsed) {}
        
        /**
         * @brief 当远端用户下线时会返回这个消息
         * @param uid User ID，从App server分配的唯一标示符
         * @param reason 用户离线的原因
         */
        virtual void OnRemoteUserOffLineNotify(const char *uid, AliEngineUserOfflineReason reason) {}
        
        /**
         * @brief 音频推流变更回调
         * @param oldState 之前的推流状态
         * @param newState 当前的推流状态
         * @param elapseSinceLastState 状态变更时间间隔
         * @param channel 当前频道id
         */
        virtual void OnAudioPublishStateChanged(AliEnginePublishState oldState, AliEnginePublishState newState, int elapseSinceLastState, const char *channel) {};

        /**
         * @brief 视频推流变更回调
         * @param oldState 之前的推流状态
         * @param newState 当前的推流状态
         * @param elapseSinceLastState 状态变更时间间隔
         * @param channel 当前频道id
         */
        virtual void OnVideoPublishStateChanged(AliEnginePublishState oldState, AliEnginePublishState newState, int elapseSinceLastState, const char *channel) {};

        /**
         * @brief 次要流推流变更回调
         * @param oldState 之前的推流状态
         * @param newState 当前的推流状态
         * @param elapseSinceLastState 状态变更时间间隔
         * @param channel 当前频道id
         */
        virtual void OnDualStreamPublishStateChanged(AliEnginePublishState oldState, AliEnginePublishState newState, int elapseSinceLastState, const char *channel) {};

        /**
         * @brief 屏幕分享推流变更回调
         * @param oldState 之前的推流状态
         * @param newState 当前的推流状态
         * @param elapseSinceLastState 状态变更时间间隔
         * @param channel 当前频道id
         */
        virtual void OnScreenSharePublishStateChanged(AliEnginePublishState oldState, AliEnginePublishState newState, int elapseSinceLastState, const char *channel) {};

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
        /**
        * @brief 屏幕分享推流变更回调
        * @param oldState 之前的推流状态
        * @param newState 当前的推流状态
        * @param elapseSinceLastState 状态变更时间间隔
        * @param channel 当前频道id
        * @param screenShareInfo 本次屏幕共享推流信息
        * @note 屏幕共享推流状态变更时与OnScreenSharePublishStateChanged回调均会触发
        */
        virtual void OnScreenSharePublishStateChangedWithInfo(AliEnginePublishState oldState, AliEnginePublishState newState, int elapseSinceLastState, const char *channel, AliEngineScreenShareInfo& screenShareInfo) {};
#endif
        /**
         * @brief 当远端用户的流发生变化时，返回这个消息
         * @param uid userId，从App server分配的唯一标示符
         * @param audioTrack 音频流类型，详见 {@link AliRTCSdk::AliEngineAudioTrack}
         * @param videoTrack 视频流类型，详见 {@link AliRTCSdk::AliEngineVideoTrack}
         */
        virtual void OnRemoteTrackAvailableNotify(const char *uid,
                                                  AliEngineAudioTrack audioTrack,
                                                  AliEngineVideoTrack videoTrack) {}

        /**
         * @brief 音频订阅情况变更回调
         * @param uid userId，从App server分配的唯一标示符
         * @param oldState 之前的订阅状态，详见 {@link AliRTCSdk::AliEngineSubscribeState}
         * @param newState 当前的订阅状态，详见 {@link AliRTCSdk::AliEngineSubscribeState}
         * @param elapseSinceLastState 两次状态变更时间间隔(毫秒)
         * @param channel 当前频道id
         */
        virtual void OnAudioSubscribeStateChanged(const char *uid,
                                                  AliEngineSubscribeState oldState, 
                                                  AliEngineSubscribeState newState,
                                                  int elapseSinceLastState,
                                                  const char *channel) {};

        /**
         * @brief 相机流订阅情况变更回调
         * @param uid userId，从App server分配的唯一标示符
         * @param oldState 之前的订阅状态，详见 {@link AliRTCSdk::AliEngineSubscribeState}
         * @param newState 当前的订阅状态，详见 {@link AliRTCSdk::AliEngineSubscribeState}
         * @param elapseSinceLastState 两次状态变更时间间隔(毫秒)
         * @param channel 当前频道id
         */
        virtual void OnVideoSubscribeStateChanged(const char *uid, 
                                                  AliEngineSubscribeState oldState, 
                                                  AliEngineSubscribeState newState,
                                                  int elapseSinceLastState,
                                                  const char *channel) {};

        /**
         * @brief 屏幕分享流订阅情况变更回调
         * @param uid userId，从App server分配的唯一标示符
         * @param oldState 之前的订阅状态，详见 {@link AliRTCSdk::AliEngineSubscribeState}
         * @param newState 当前的订阅状态，详见 {@link AliRTCSdk::AliEngineSubscribeState}
         * @param elapseSinceLastState 两次状态变更时间间隔(毫秒)
         * @param channel 当前频道id
         */
        virtual void OnScreenShareSubscribeStateChanged(const char *uid,
                                                        AliEngineSubscribeState oldState, 
                                                        AliEngineSubscribeState newState,
                                                        int elapseSinceLastState,
                                                        const char *channel) {};

        /**
         * @brief 大小订阅情况变更回调
         * @param uid userId，从App server分配的唯一标示符
         * @param oldStreamType 之前的订阅的大小流类型，详见 {@link AliRTCSdk::AliEngineVideoStreamType}
         * @param newStreamType 当前的订阅的大小流类型，详见 {@link AliRTCSdk::AliEngineVideoStreamType}
         * @param elapseSinceLastState 大小流类型变更时间间隔(毫秒)
         * @param channel 当前频道id
         */
        virtual void OnSubscribeStreamTypeChanged(const char *uid,
                                                  AliEngineVideoStreamType oldStreamType, 
                                                  AliEngineVideoStreamType newStreamType, 
                                                  int elapseSinceLastState, 
                                                  const char *channel) {};
        
        /**
         * @brief 网络质量变化时发出的消息
         * @param uid  网络质量发生变化的用户uid
         * @param upQuality 上行网络质量，详见AliEngineNetworkQuality
         * @param downQuality 下行网络质量，详见AliEngineNetworkQuality
         * @note 当网络质量发生变化时触发，uid为空时代表用户自己的网络质量发生变化
         */
        virtual void OnNetworkQualityChanged(const char *uid,
                                             AliEngineNetworkQuality upQuality,
                                             AliEngineNetworkQuality downQuality) {}
                                             
        /**
         * @brief 是否推静态图片。在通过SetPublishImage设置了替代图片，上行网络状态差的情况下回调。
         * @param isStaticFrame  true , 上行网络差，开始推静态图片。false，上行网络恢复，推正常采集数据。
         */
        virtual void OnPublishStaticVideoFrame(AliEngineVideoTrack trackType, bool isStaticFrame) {}
        
        /**
         * @brief 被服务器踢出频道的消息
         * @param code onBye类型，详见AliEngineOnByeType
         */
        virtual void OnBye(int code) {}
        
        /**
         * @brief 如果engine出现warning，通过这个消息通知app
         */
        virtual void OnOccurWarning(int warn, const char *msg) {}
        
        /**
         * @brief 如果engine出现error，通过这个消息通知app
         */
        virtual void OnOccurError(int error, const char *msg) {}
        
        /**
         * @brief 当前设备性能不足
         */
        virtual void OnPerformanceLow() {}

        /**
         * @brief 当前设备性能恢复
         */
        virtual void OnPerformanceRecovery() {}
        
        /**
         * @brief 远端用户的第一帧视频帧显示时触发这个消息
         * @param uid User ID，从App server分配的唯一标示符
         * @param videoTrack 屏幕流或者相机流，参考 {@link AliEngineVideoTrack}
         * @param width 视频宽度
         * @param height 视频高度
         * @param elapsed 本地用户加入频道直至该回调触发的延迟总耗时（毫秒）
         * @note 该接口用于远端用户的第一帧视频帧显示时的回调
         */
        virtual void OnFirstRemoteVideoFrameDrawn(const char *uid,
                                                  AliEngineVideoTrack videoTrack,
                                                  int width, 
                                                  int height, 
                                                  int elapsed) {}
        
        /**
         * @brief 预览开始显示第一帧视频帧时触发这个消息
         * @param width 本地预览视频宽度
         * @param height 本地预览视频高度
         * @param elapsed 从本地用户加入频道直至该回调触发的延迟总耗时（毫秒）
         * @note 该接口用于预览开始显示第一帧视频帧时的回调
         */
        virtual void OnFirstLocalVideoFrameDrawn(int width, int height, int elapsed) {}
        
        /**
         * @brief 音频首包发送回调
         * @param timeCost 耗时
         */
        virtual void OnFirstAudioPacketSend(int timeCost) {};

        /**
         * @brief 音频首包接收回调
         * @param uid uid
         * @param timeCost 耗时
        */
        virtual void OnFirstAudioPacketReceived(const char* uid, int timeCost) {}

        /**
         * @brief 已解码远端音频首帧回调
         * @param uid  用户userId
         * @param elapsed  从本地用户加入频道直至该回调触发的延迟, 单位为毫秒
         */
        virtual void OnFirstRemoteAudioDecoded(const char* uid, int elapsed) {}
        
        /**
         * @brief 视频首包发送回调
         * @param videoTrack 发送视频track，参考 {@link AliEngineVideoTrack}
         * @param timeCost 耗时（毫秒）
         * @note 该接口用于视频首包发送的回调
         */
        virtual void OnFirstVideoPacketSend(AliEngineVideoTrack videoTrack, int timeCost) {};

        /**
         * @brief 视频首包接收回调
         * @param uid User ID，从App server分配的唯一标示符
         * @param videoTrack 接收视频track，参考 {@link AliEngineVideoTrack}
         * @param timeCost 耗时（毫秒）
         * @note 该接口用于视频首包接收的回调
         */
        virtual void OnFirstVideoPacketReceived(const char* uid,
                                                AliEngineVideoTrack videoTrack, 
                                                int timeCost) {}

        /**
         * @brief 收到远端用户视频首帧的回调
         * @param uid User ID，从App server分配的唯一标示符
         * @param videoTrack 接收视频track，参考 {@link AliEngineVideoTrack}
         * @param timeCost 耗时（毫秒）
         * @note 该接口用于收到远端用户视频首帧的回调
        */
        virtual void OnFirstVideoFrameReceived(const char* uid,
                                          AliEngineVideoTrack videoTrack,
                                          int timeCost) {};
        
        /**
         * @brief 网络断开
         */
        virtual void OnConnectionLost() {}
        
        /**
         * @brief 开始重连
         */
        virtual void OnTryToReconnect() {}
        
        /**
         * @brief 重连成功
         */
        virtual void OnConnectionRecovery() {}
        
        /**
         * @brief 网络连接状态改变的回调
         * @param status 当前网络链接状态，参考AliEngineConnectionStatus
         * @param reason 网络链接状态改变原因，参考AliEngineConnectionStatusChangeReason
         */
        virtual void OnConnectionStatusChange(int status, int reason) {};

        /**
         * @brief 对端用户停止音频数据发送通知
         * @param uid 执行muteAudio的用户
         * @param isMute true:静音 false:未静音
         */
        virtual void OnUserAudioMuted(const char* uid, bool isMute) {}

        /**
         * @brief 对端用户发送视频黑帧数据发送通知
         * @param uid 执行muteVideo的用户
         * @param isMute true:推流黑帧 false:正常推流
         * @note 该接口用于对端用户发送视频黑帧数据时的回调
         */
        virtual void OnUserVideoMuted(const char* uid, bool isMute) {}
        
        /**
         * @brief 对端用户关闭相机流采集发送通知
         * @param uid 执行EnableLocalVideo的用户
         * @param isEnable true:打开相机流采集 false:关闭相机流采集
         * @note 该接口用于对端用户关闭相机流采集时的回调
        */
        virtual void OnUserVideoEnabled(const char* uid, bool isEnable) {}

        /**
         * @brief 用户audio被中断通知（一般用户打电话等音频被抢占场景）
         * @param uid audio被中断的用户
         */
        virtual void OnUserAudioInterruptedBegin(const char* uid) {}

        /**
         * @brief 用户音频中断结束通知（对应onUserAudioInterruptedBegin）
         * @param uid audio中断结束的用户
         */
        virtual void OnUserAudioInterruptedEnded(const char* uid) {}
        
        /**
         * @brief 用户伴奏开始播放
         * @param uid 用户
         */
        virtual void OnRemoteAudioAccompanyStarted(const char* uid) {}
        
        /**
         * @brief 用户伴奏结束播放
         * @param uid 用户
         */
        virtual void OnRemoteAudioAccompanyFinished(const char* uid) {}

        /**
         * @brief 远端用户应用退到后台
         * @param uid 用户
         */
        virtual void OnUserWillResignActive(const char* uid) {}

        /**
         * @brief 远端用户应用返回前台
         * @param uid 用户
         */
        virtual void OnUserWillBecomeActive(const char* uid) {}
        
        /**
         * @brief 当前角色变化通知回调
         * @param oldRole 切换前的角色
         * @param newRole 切换后的角色
         * @note 调用setClientRole方法切换角色成功时触发此回调
         */
        virtual void OnUpdateRoleNotify(const AliEngineClientRole oldRole,
                                        const AliEngineClientRole newRole) {}

        /**
         * @brief 订阅的音频音量回调，其中callid为"0"表示本地推流音量，"1"表示远端混音音量，其他表示远端用户音量
         * @param volumeInfo 说话人结构体信息
         * @param totalVolume 混音后的总音量，范围[0,255]。在本地用户的回调中，totalVolume;为本地用户混音后的音量；在远端用户的回调中，totalVolume; 为所有说话者混音后的总音量
         * @param volumeInfoCount 回调的说话人的个数
         */
        virtual void OnAudioVolumeCallback(const AliEngineUserVolumeInfo* volumeInfo, int volumeInfoCount, int totalVolume) {}
        
        /**
         * @brief 订阅的当前说话人，当前时间段说话可能性最大的用户uid。如果返回的uid为0，则默认为本地用户
         */
        virtual void OnActiveSpeaker(const char *uid) {}
        
        /**
         * @brief 伴奏/音效播放回调
         * @param type 当前播放状态
         * @param errorCode errorCode
         */
        virtual void OnAudioPlayingStateChanged(AliEngineAudioPlayingType type,
                                                AliEngineAudioPlayingErrorCode errorCode) {}
        /**
         * @brief 伴奏/音效播放结束回调
         * @param soundId soundId
        */
        virtual void OnAudioEffectFinished(int soundId) {}

        /**
         * @brief 网络质量探测回调
         * @param networkQuality 网络质量 {@link AliEngineNetworkQuality}
         * @note 当调用 {@link AliEngine::StartLastmileDetect} 后会触发该回调
         */
        virtual void OnLastmileDetectResultWithQuality(AliEngineNetworkQuality networkQuality) {}
        
        /**
         * @brief 音频采集设备测试回调
         * @param level 音频采集设备音量值
         */
        virtual void OnAudioDeviceRecordLevel(int level) {};

        /**
         * @brief 音频播放设备测试回调
         * @param level 音频采集设备音量值
         */
        virtual void OnAudioDevicePlayoutLevel(int level) {};

        /**
         * @brief 音频播放设备测试结束(音频文件播放完毕)
         */
        virtual void OnAudioDevicePlayoutEnd() {};
        
        /**
         * @brief 文件录制回调事件
         * @param event 录制事件，0：录制开始，1：录制结束，2：打开文件失败，3：写文件失败
         * @param filePath 录制文件路径
         * @note 该接口用于文件录制时的事件回调
         */
        virtual void OnMediaRecordEvent(int event, const char* filePath) {}

        /**
         * @brief 当前会话统计信息回调
         * @param stats 会话统计信息
         * @note SDK每两秒触发一次此统计信息回调
         */
        virtual void OnStats(const AliEngineStats& stats) {}

        /**
         * @brief 本地视频统计信息
         * @param localVideoStats 本地视频统计信息
         * @note SDK每两秒触发一次此统计信息回调
         */
        virtual void OnLocalVideoStats(const AliEngineLocalVideoStats& localVideoStats) {}

        /**
         * @brief 远端视频统计信息
         * @param remoteVideoStats 远端视频统计信息
         * @note SDK每两秒触发一次此统计信息回调
         */
        virtual void OnRemoteVideoStats(const AliEngineRemoteVideoStats& remoteVideoStats) {}
        
        /**
         * @brief 本地音频统计信息
         * @param localAudioStats 本地视频统计信息
         * @note SDK每两秒触发一次此统计信息回调
         */
        virtual void OnLocalAudioStats(const AliEngineLocalAudioStats& localAudioStats) {}
        
        /**
         * @brief 远端音频统计信息
         * @param remoteAudioStats 远端视频统计信息
         * @note SDK每两秒触发一次此统计信息回调
         */
        virtual void OnRemoteAudioStats(const AliEngineRemoteAudioStats& remoteAudioStats) {}
        
        /**
         * @brief 低延时互动直播模式start回调
         * @param result 是否start成功
         * @note 该回调仅在低延时互动模式且角色为观众时，调用 {@link AliEngine::StartLiveStreaming} 才会回调
         * @deprecated
         */
        virtual void OnStartLiveStreamingResult(int result) {}
        
        /**
         * @brief 收到媒体扩展信息回调
         * @param uid 发送用户userId
         * @param message 扩展信息内容
         * @param size 扩展信息长度
         * @note 当一端通过 {@link AliEngine::SendMediaExtensionMsg} 发送信息后，其他端通过该回调接收数据
         */
        virtual void OnMediaExtensionMsgReceived(const char* uid,unsigned char* message, unsigned int size) {};

        /**
         * @brief 音频设备状态变更
         * @param deviceInfo  外接设备信息
         * @param deviceType  外接设备类型
         * @param deviceState 外接设备状态
         */
        virtual void OnAudioDeviceStateChanged(const AliEngineDeviceInfo& deviceInfo, AliEngineExternalDeviceType deviceType, AliEngineExternalDeviceState deviceState) {};

        /**
         * @brief 视频设备状态变更
         * @param deviceInfo  外接设备信息
         * @param deviceType  外接设备类型
         * @param deviceState 外接设备状态
         */
        virtual void OnVideoDeviceStateChanged(const AliEngineDeviceInfo& deviceInfo, AliEngineExternalDeviceType deviceType, AliEngineExternalDeviceState deviceState) {} ;

        /**
         * @brief 下行消息通道(接收消息) 
         * @param messageInfo 消息内容 
         * @note 该接口接收到下行消息后，使用 {@link AliEngine::SendDownlinkMessageResponse} 发送反馈消息
         * @note 已废弃使用
         * @deprecated
         */
        virtual void OnDownlinkMessageNotify(const AliEngineMessage &messageInfo) {};

        /** 
         * @brief 上行消息返回结果(接收消息)
         * @param resultInfo 发送结果
         * @note 使用 {@link AliEngine::SendUplinkMessage} 发送消息后，会触发该接口接收上行消息反馈
         * @note 已废弃使用
         * @deprecated
         */
        virtual void OnUplinkMessageResponse(const AliEngineMessageResponse &resultInfo) {};

#if (defined(__APPLE__) && TARGET_OS_IOS)
        /**
         * @brief 语音路由发生变化回调
         * @param routing 当前使用的语音路由
         */
        virtual void OnAudioRouteChanged(const AliEngineAudioRouteType routing) {};
#endif

        /**
         * @brief 分辨率变化回调
         * @param uid 用户id
         * @param track 变化视频track
         * @param width 当前视频宽
         * @param height 当前视频高
         * @note 已废弃使用
         */
        virtual void OnVideoResolutionChanged(const char* uid,
          AliEngineVideoTrack track,
          int width,
          int height) {};
        
        /**
         * @brief 截图回调
         * @param userId 用户id
         * @param videoTrack 截图视频track，参考 {@link AliEngineVideoTrack}
         * @param buffer 成功返回截图数据，失败为NULL
         * @param width 截图宽度
         * @param height 截图高度
         * @param success 截图是否成功
         * @note 该接口用于截图回调
         */
        virtual void OnSnapshotComplete(const char* userId, AliEngineVideoTrack videoTrack, void* buffer, int width, int height, bool success) {}

        /**
         * @brief 旁路推流状态改变回调
         * @param streamUrl 流地址
         * @param state 推流状态, 参考 {@link AliEngineLiveTranscodingState}
         * @param errCode 错误码, 参考 {@link AliEngineLiveTranscodingErrorCode}
         * @note 该接口用于旁路推流状态改变的回调
         */
        virtual void OnPublishLiveStreamStateChanged(const char* streamUrl ,AliEngineLiveTranscodingState state ,AliEngineLiveTranscodingErrorCode errCode){};
        
        /**
         * @brief 旁路任务状态改变回调
         * @param streamUrl  流地址
         * @param state 任务状态, 参考 {@link AliEngineTrascodingPublishTaskStatus}
         * @note 该接口用于旁路任务状态改变的回调
         */
        virtual void OnPublishTaskStateChanged(const char* streamUrl, AliEngineTrascodingPublishTaskStatus state){};

        /**
         * @brief 跨频道转推状态变化通知
         * @param state 当前连麦状态，参考 {@link AliEngineChannelRelayState}
         * @param code 当前错误码，参考 {@link AliEngineChannelRelayErrorCode}
         * @param msg 状态描述信息
         */
        virtual void OnChannelRelayStateChanged(int state, int code, const char* msg){};

        /**
         * @brief 跨频道转推事件通知
         * @param state 状态码，参考 {@link AliEngineChannelRelayEvent}
         */
        virtual void OnChannelRelayEvent(int state){};
        
        /**
         * @brief 用户remote video change通知
         * @param uid 需要被通知的用户
         * @param track 变化视频track
         * @param state 视频状态的类型
         * @param reason 触发状态变化的原因
         */
        virtual void OnRemoteVideoChanged(const char* uid, AliEngineVideoTrack trackType, const AliEngineVideoState state, const AliEngineVideoReason reason) {};

        /**
         * @brief 用户AliEngineAuthInfo authInfo即将过期通知,30秒后过期
         */
        virtual void OnAuthInfoWillExpire() {};

        /**
         * @brief 用户调用需要鉴权的接口，服务端返回信息过期
         */
        virtual void OnAuthInfoExpired() {};

        /**
         * @brief Qos参数发生变化通知
         * @param trackType 变化视频track
         * @param paramter qos参数结构体
         */
        virtual void OnRequestVideoExternalEncoderParameter(AliEngineVideoTrack trackType, const AliEngineVideoExternalEncoderParameter& paramter) {};
        /**
         * @brief Qos请求帧类型发生变化通知
         * @param trackType 变化视频track
         * @param frame_type 请求参考帧类型
         */
        virtual void OnRequestVideoExternalEncoderFrame(AliEngineVideoTrack trackType, AliEngineVideoEncodedFrameType frame_type) {};

    };

    /**
     * @brief RTC引擎的主要控制类
     */
    class ALI_RTC_API AliEngine
    {
    public:
        /**
         * @brief 获取一个AliEngineEngine实例
         * @param extras 用于接收来自客户灰度下发的参数
         */
        static AliEngine *Create(const char *extras);

        /**
         * @brief 销毁 {@link AliEngine}
         * @details 调用该方法将会释放所有内部使用的资源,当完成音视频通信之后都建议调用该方法释放实例.调用该方法后，你将不能再使用 {@link AliEngine} 的其他方法和任何回调，如需要再次使用需要重新调用 {@link AliEngine::Create} 方法创建一个新的实例。
         * @note 该方法为同步调用,需要等待内部资源释放之后才能执行其他方法,为避免主线程阻塞，建议开发者放在子线程调用该方法，但需要注意的是如需在销毁后再次创建 {@link AliEngine} 实例，请开发者务必保证 Destroy 方法执行结束后再创建实例。
         * @note 为避免死锁，不建议在任何SDK的回调中调用本方法
         */
        static void Destroy();
        
        /**
         * @brief 获取sdk版本号
         * @return SDK版本号
         * @note 在任何时刻都可以调用
         */
        static const char *GetSDKVersion();
        
        /**
         * @brief 设置H5兼容模式
         * @param comp true: 兼容H5; false: 传统模式，不兼容H5
         */
        static void SetH5CompatibleMode(bool comp);
        
        /**
         * @brief 检查当前是否兼容H5
         * @return true: 兼容H5; false: 不兼容H5
         */
        static bool GetH5CompatibleMode();
        
        /**
         * @brief 设置SDK日志文件保存路径
         * @param logDirPath 日志文件保存绝对路径
         * @return 0为成功，非0失败
         * @note 如需调用此接口，请在调用所有SDK接口前先进行设置，避免日志出现丢失，同时App必须保证指定的目录已存在且可写入
         */
        static int SetLogDirPath(const char *logDirPath);

        /**
         * @brief 设置日志等级
         * @param logLevel Log级别，详见AliEngineLogLevel枚举类型
         */
        static void SetLogLevel(AliEngineLogLevel logLevel);

        /**
         * @brief 上报日志
         */
        static void UploadLog();
        
        /**
         * @brief 获取错误码描述
         * @param errorCode 错误码
         * @return 错误码描述字符串
         */
        static const char* GetErrorDescription(int errorCode);
        
        /**
         * @brief 获取编码分辨率
         */
        static void GetEncodeParam(int *width, int *height);
        
        /**
         * @brief 获取功能接口实例
         * @param iid type类型
         * @param pInterface 示例
         * @return 成功返回实例对象，失败返回nullptr
         */
        virtual int QueryInterface(AliEngineInterfaceIdType iid, void** pInterface) = 0;

        /**
         * @brief 设置相关监听事件回调
         * @dedatils {@link AliEngineEventListener}类是SDK向应用发送自身回调事件的通知,应用开发者需要实现该接口类的方法来获取相关事件通知。默认所有接口都有空实现，开发者不需要实现所有方法，可根据自身业务来实现对应的事件方法。
         * @param listener  用于接收来自engine的消息
         * @note 所有的回调方法都是SDK内部的线程,不可以做UI操作，有UI相关操作需要抛主线程操作
         * @note 不建议在回调方法中做耗时操作,如调用AliEngine本身的Destroy方法，这将有可能引起不必要的阻塞从而影响SDK的运行
         */
        virtual int SetEngineEventListener(AliEngineEventListener *listener) = 0;

        /**
         * @brief 设置音频模式还是音视频模式
         * @param audioOnly  true表示只有音频推流和拉流；false表示音视频都支持
         */
        virtual int SetAudioOnlyMode(bool audioOnly) = 0;
        
        /**
         * @brief 设置频道模式
         * @details 客户根据业务需求配置不同的频道模式，AliRTC会根据不用的频道模式模式采用不用的策略，目前主要提供通信模式(默认)、互动模式、低延迟互动直播模式
         * @param channelProfile 频道模式类型,详细请参考 {@link AliEngineChannelProfile}
         *  @return
         *  - 0: 成功
         *  - <0: 失败
         * @note
         *  - 相同频道内的用户必须使用同一种频道场景
         *  
         */
        virtual int SetChannelProfile(const AliEngineChannelProfile channelProfile) = 0;
        
        /**
         * @brief 设置直播场景 {@link AliEngineChannelProfile} 设置为 {@link AliEngineChannelProfile::AliEngineInteractiveLive} 下的用户角色。
         * @details 异步方法，在加入频道后，调用本方法成功切换角色后，将会收到 {@link AliEngineEventListener::OnUpdateRoleNotify} 回调；远端用户将会触发 {@link AliEngineEventListener::onRemoteUserOnLineNotify} 或 {@link AliEngineEventListener::onRemoteUserOffLineNotify}回调
         * 在使用 {@link AliEngineChannelProfile} 设置为 {@link AliEngineChannelProfile::AliEngineInteractiveLive} 模式，在加入频道前，用户需要通过本方法设置观众角色（默认）或互动角色。在加入频道后，用户可以通过本方法切换用户模式。
         *
         * @param clientRole 用户角色类型 {@link AliRTCSdkClientRole}
         * @return
         *  - 0: 成功
         *  - <0: 失败
         */
        virtual int SetClientRole(const AliEngineClientRole clientRole) = 0;
        
        /**
         * @brief 获取用户角色
         * @return 用户角色类型
         */
        virtual AliEngineClientRole GetClientRole() = 0;

        /**
         * @brief 设置视频编码属性
         * @param config 预定义的编码属性，详见AliEngineVideoEncoderConfiguration
        */
        virtual void SetVideoEncoderConfiguration(const AliEngineVideoEncoderConfiguration& config) = 0;
        
        /**
         * @brief 设置屏幕共享编码属性
         * @param config 预定义的屏幕共享编码属性，详见AliEngineScreenShareEncoderConfiguration
        */
        virtual void SetScreenShareEncoderConfiguration(const AliEngineScreenShareEncoderConfiguration& config) = 0;
        
        /**
         * @brief 该方法让用户加入频道，一个频道内可以加入多个用户进行互相通话.
         * @param authInfo    认证信息，从App Server获取。
         * @param userName    任意用于显示的用户名称。不是User ID
         * @return
         * - 0: 成功
         * - <0: 失败
         * @note
         *    - 异步接口。是否成功入会，通过 {@link AliEngineEventListener::OnJoinChannelResult}判断 
         *    - 正常情况一个Appid对应一个App，只有同一个AppId的应用可进行互相童话,不同AppId和channelID不同都不能互通
         *    - 当入会成功后，会触发远端用户收到 {@link AliEngineEventListener::OnJoinChannelResult} 回调
         *    - 如果已在会中想重新入会，需要先调用 {@link LeaveChannel} 离会，且确保 {@link AliEngineEventListener::OnLeaveChannelResult} 回调收到后，再次调用进行入会
         *    - 如果用户是观众角色，已在会中，可以通过  {@link SwitchChannel}  进行快速切换其他房间
         *    - 用户加入频道后，默认订阅频道内所有其他用户的音视频流，默认推送音视频流到远端，因此将会产生计费，如果想要取消默认订阅可以{@link JoinChannel} 前调用 {@link SetDefaultSubscribeAllRemoteAudioStreams} 和 {@link SetDefaultSubscribeAllRemoteVideoStreams}
         */
        virtual int JoinChannel(const AliEngineAuthInfo &authInfo,
                                 const char *userName) = 0;

        /**
         * @brief 以josn字符串的格式，设置自定义属性
         * @param parameter 自定义属性参数
         * @return 0为成功，非0失败
        */
        virtual int SetParameter(const char* parameter) = 0;
        
        /**
         * @brief  离开频道,即挂断或者停止童话
         * @details 如果当前不在频道内，{@link LeaveChannel} 不会有任何影响。{@link LeaveChannel} 会产生消息通知频道内其他用户。
         * @details 调用 {@link JoinChannel}  后必须要调用 {@link LeaveChannel} 离开频道，否则无法进入下一个频道通话。
         * @details 异步方法，成功调用后需要收到 {@link AliEngineEventListener::OnLeaveChannelResult} 才会真正退出频道，离开频道成功远端用户会触发会收到 {@link AliEngineEventListener::OnRemoteUserOnLineNotify}回调。
         * @return
         * - 0: 成功
         * - <0: 失败
         * @note
         *  - 如果调用了 {@link LeaveChannel} 后立刻调用 {@link Destroy} 方法，SDK将会无法触发 {@link AliEngineEventListener::OnLeaveChannelResult}
         *
         */
        virtual int LeaveChannel() = 0;

        /**
         * @brief 切换频道
         * @details 当我们已经在一个频道中想要加入另外一个频道时，通常我们需要离会之后在收到离会回调之后再加入到另外一个频道中，调用方法可以实现快速切换频道。
         * @details 成功调用该方切换频道后，本地会先收到离开原频道的回调 {@link AliEngineEventListener::OnLeaveChannelResult} ，再收到成功加入新频道的回调 {@link AliEngineEventListener::OnJoinChannelResult}。
         * @param authInfo 鉴权信息，从App Server获取
         * @return
         * - 0: 成功
         * - <0: 失败
         * @note 本方法只允许在直播模式AliRtcInteractiveLive下，观看角色AliRtcClientRoleLive使用
         * @note 返回AliEngineErrorInvaildState请确认是否频道模式/角色不匹配，或当前未加入任何频道中
         * @note 返回AliEngineErrorInvaildArgument请确认鉴权信息是否合法，或者是否加入相同频道
         * @note 返回AliEngineErrorInner为SDK内部状态错误
         * @note 调用此方法成功切换频道后，SDK会先触发离开原频道的回调OnLeaveChannelResult，在返回加入新频道的回调OnJoinChannelResult
        */
        virtual int SwitchChannel(const AliEngineAuthInfo &authInfo) = 0;

        /**
         * @brief 设置本地预览显示视图
         * @param renderConfig renderConfig 本地视频显示属性, 详细见{@link AliEngineVideoCanvas}
         * @param track  只支持{@link AliEngineVideoTrackCamera}和{@link AliEngineVideoTrackScreen}
         * @return
         * - 0 : 成功
         * - < 0 : 失败
         * @note 支持joinChannel之前和之后切换窗口。如果{@link AliEngineVideoCanvas::displayView}为null，则停止显示。
         *       如果需要重新设置{@link AliEngineVideoCanvas::renderMode}，请保持renderConfig中其他属性不变，仅修改
         *       {@link AliEngineVideoCanvas::renderMode}。
         *       如果需要重新设置{@link AliEngineVideoCanvas::mirrorMode}，请保持renderConfig中其他属性不变，仅修改
         *       {@link AliEngineVideoCanvas::mirrorMode}。
         */
        virtual int SetLocalViewConfig(AliEngineVideoCanvas renderConfig,
                                         AliEngineVideoTrack track) = 0;
        
        /**
         * @brief 设置摄像头采集偏好
         * @param config 采集偏好
         *      - preference: {@link AliEngineCaptureOutputPreference::AliEngineCaptureOutputPreferencePreview} 高清预览，采集优先保证视频预览质量
         *                    {@link AliEngineCaptureOutputPreference::AliEngineCaptureOutputPreferencePerformance} 采集选择最接近推流的分辨率，优先保证设备性能
         *                    {@link AliEngineCaptureOutputPreference::AliEngineCaptureOutputPreferenceAuto} 自动调整采集分辨率
         *      - cameraDirection: 设置采集方向，前置 或 后置，仅对android和ios有效
         * @return 0为成功，非0失败
         * @note 必须在打开摄像头之前设置，如{@link StartPreview}，{@link JoinChannel}之前设置
         */
        virtual int SetCameraCapturerConfiguration(const AliEngineCameraCapturerConfiguration& config) = 0;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
        /**
         * @brief 设备方向
         * @param mode 设备方向
         * @return
         * - 0 : 成功
         * - < 0 : 失败
         */
        virtual int SetDeviceOrientationMode(AliEngineOrientationMode mode) = 0;
#endif

        /**
         * @brief 开启本地视频预览
         * @return
         * - 0 : 成功
         * - < 0 : 失败
         * @note 如果没有调用{@link SetLocalViewConfig}设置显示的view，则无法预览。
         *       可以在{@link JoinChannel}之前就开启预览会自动打开摄像头。
         */
        virtual int StartPreview() = 0;
        
        /**
         * @brief 关闭本地视频预览
         * @return
         * - 0 : 成功
         * - < 0 : 失败
         * @note {@link LeaveChannel}会自动停止本地预览；如果没有在推相机流，则会自动关闭摄像头。
         */
        virtual int StopPreview() = 0;
        
        /**
         * @brief 禁用或启用本地视频采集
         * @param enabled
         * - true : 启用本地视频采集
         * - false : 禁用本地视频采集
         * @return
         * - 0 : 成功
         * - < 0 : 失败
         * @note 默认为开启状态, 通过监听{@link AliEngineEventListener::OnUserVideoEnabled}获取用户是否禁用或启用本地视频采集状态。
         */
        virtual int EnableLocalVideo(bool enabled) = 0;

        /**
         * @brief 停止/恢复本地视频数据数据发送
         * @param mute true表示视频数据发送黑帧；false表示恢复正常
         * @param track 只支持{@link AliEngineVideoTrackCamera}
         * @return
         * - 0: 为成功
         * - 非0: 失败
         * @note 此接口只是控制指定视频流上是否发送黑帧，采集和数据发送不会停止
         * @note 如果需要关闭采集请使用EnableLocalVideo接口，如果需要中止视频数据发送请使用PublishLocalVideoStream接口
         */
        virtual int MuteLocalCamera(bool mute, AliEngineVideoTrack track) = 0;

        /**
         * @brief 是否允许推送次要视频流
         * @param enabled 是否开启/关闭次要视频流推送
         - true: 开启次要视频流推送
         - false: 关闭次要视频流推送
         * @return
         - 0: 设置成功
         - <0: 设置失败，返回错误码
         * @note 次要视频流只在推送视频流的前提下才会推送，设置推送次要视频流时，请确认已通过{@link PublishLocalVideoStream}方法开启视频流推送
         * @note SDK默认设置不推送次要视频流，在加入频道前也可以调用此接口修改默认值，并在推送视频流时生效
         */
        virtual int PublishLocalDualStream(bool enabled) = 0;

        /**
         * @brief 查询当前是否设置推送次要视频流
         * @return 
         - true: 已设置推送
         - false: 未设置推送
         * @note SDK默认设置不推送次要视频流，如果需要推送次要视频流，可以通过接口{@link PublishLocalDualStream}方法设置为推送
         */
        virtual bool IsDualStreamPublished() = 0;

        /**
         * @brief 是否推送本地视频(摄像头)流
         * @param enabled 是否开启/关闭本地视频流推送
         - true: 开启视频流推送
         - false: 关闭视频流推送
         * @return
         - 0: 设置成功
         - <0: 设置失败，返回错误码
         * @note SDK默认设置推送视频流，在加入频道前也可以调用此接口修改默认值，并在加入频道成功时生效
         */
        virtual int PublishLocalVideoStream(bool enabled) = 0;

        /**
         * @brief 是否推送本地音频流
         * @param enabled 是否开启/关闭本地音频流推送
         - true: 开启音频流推送
         - false: 关闭音频流推送
         * @return
         - 0: 设置成功
         - <0: 设置失败，返回错误码
         * @note SDK默认设置推送音频流，在加入频道前也可以调用此接口修改默认值，并在加入频道成功时生效
         */
        virtual int PublishLocalAudioStream(bool enabled) = 0;
        
        /**
         * @brief 停止/恢复本地音频数据发送
         * @param mute true表示本地音频发送静音帧；false表示恢复正常
         * @return 0为成功，非0失败
         * @note mute只是发送音频数据为静音帧，采集和编码模块仍然在工作
         */
        virtual int MuteLocalMic(bool mute, AliEngineMuteLocalAudioMode mode = AliEngineMuteLocalAudioModeDefault) = 0;

        /**
         * @brief 设置本地预览显示视图
         * @param renderConfig renderConfig 本地视频显示属性, 详细见{@link AliEngineVideoCanvas}
         * @param uid User ID，从App server分配的唯一标示符
         * @param track  只支持{@link AliEngineVideoTrackCamera}和{@link AliEngineVideoTrackScreen}
         * @return
         * - 0 : 成功
         * - < 0 : 失败
         * @note 支持joinChannel之前和之后切换窗口。如果{@link AliEngineVideoCanvas::displayView}为null，则停止显示。
         *       如果需要重新设置{@link AliEngineVideoCanvas::renderMode}，请保持renderConfig中其他属性不变，仅修改
         *       {@link AliEngineVideoCanvas::renderMode}。
         *       如果需要重新设置{@link AliEngineVideoCanvas::mirrorMode}，请保持renderConfig中其他属性不变，仅修改
         *       {@link AliEngineVideoCanvas::mirrorMode}。
         */
        virtual int SetRemoteViewConfig(AliEngineVideoCanvas renderConfig,
                                          const char *uid,
                                          AliEngineVideoTrack track) = 0;
        
        /**
         * @brief 更新渲染配置
         * @param renderConfig config包含了窗口以及渲染方式
         * @return 0为成功，非0失败
         */
        virtual int UpdateViewConfig(AliEngineVideoCanvas renderConfig) = 0;
        
        /**
         * @brief 设置订阅相机流格式，大流或小流
         * @param uid  userId，从App server分配的唯一标示符
         * @param streamType 流类型
         - AliEngineVideoStreamTypeNone:无效参数，设置不会有任何效果
         - AliEngineVideoStreamTypeHigh:大流
         - AliEngineVideoStreamTypeLow:小流
         * @return
         - 0:设置成功
         - <0:设置失败
         * @note 推流端当前默认不推送小流，只有发送端调用了{@link AliEngine::PublishLocalDualStream(true)} 打开双流模式，接收端才可以选择订阅大流还是小流，否则订阅的只能是大流；
         */
        virtual int SetRemoteVideoStreamType(const char* uid,
                                             AliEngineVideoStreamType streamType) = 0;
      
        /**
         * @brief 设置默认订阅的相机流格式，大流或小流；如果不设置，则默认订阅大流；
         * @param streamType 流类型
         - AliEngineVideoStreamTypeNone:无效参数，设置不会有任何效果
         - AliEngineVideoStreamTypeHigh:(Default)大流
         - AliEngineVideoStreamTypeLow:小流
         * @return
         - 0:设置成功
         - <0:设置失败
         */
        virtual int SetRemoteDefaultVideoStreamType(AliEngineVideoStreamType streamType) = 0;
      
        /**
         * @brief 设置是否默认订阅音频流
         * @param sub 是否默认订阅音频流
         - true:(Default)默认订阅音频流，
         - false:默认不订阅音频流
         * @return
         - 0:设置成功
         - <0:设置失败
         * @note
         - 入会前入会后均可调用；
         - 如果在加入频道前调用 SetDefaultSubscribeAllRemoteAudioStreams (false)，则入会后默认不再订阅任何音频流；
         - 如果在加入频道后调用 SetDefaultSubscribeAllRemoteAudioStreams (false)，默认不再订阅设置后加入频道的用户的音频流；
         - 不管是否默认订阅，都可以调用 {@link AliEngine::SubscribeRemoteAudioStream}，对指定的用户进行订阅或取消订阅操作；
         - 订阅行为统一受到 {@link AliEngine::SubscribeAllRemoteAudioStreams} 这个总开关控制，假设 {@link AliEngine::SubscribeAllRemoteAudioStreams} 设置为false，则订阅全部关闭，其他启动行为全部不生效；
         */
        virtual int SetDefaultSubscribeAllRemoteAudioStreams(bool sub) = 0;

        /**
         * @brief 停止/恢复订阅所有远端音频流
         * @param sub 是否订阅所有远端音频流
         - true:订阅所有用户的音频流
         - false:停止订阅所有用户的音频流
         * @return
         - 0:设置成功
         - <0:设置失败
         * @note
         - 入会前入会后均可以调用；
         - 如果设置了 SubscribeAllRemoteAudioStreams(false)，后面调用 {@link AliEngine::SetDefaultSubscribeAllRemoteAudioStreams} 和 {@link AliEngine::SubscribeRemoteAudioStream} 都不会生效；
         */
        virtual int SubscribeAllRemoteAudioStreams(bool sub) = 0;

        /**
         * @brief 停止/恢复订阅特定远端用户的音频流
         * @param uid userId，从App server分配的唯一标示符
         * @param sub 是否订阅远端用户的音频流
         - true:订阅指定用户的音频流
         - false:停止订阅指定用户的音频流
         * @return
         - 0:设置成功
         - <0:设置失败
         * @note
         - 如果之前有调用过 {@link AliEngine::SubscribeAllRemoteAudioStreams(false)} 停止订阅所有远端音频，则此接口调用无效；
         - {@link AliEngine::SubscribeAllRemoteAudioStreams} 是全局控制，SubscribeRemoteAudioStream 是单独控制。
         */
        virtual int SubscribeRemoteAudioStream(const char* uid, bool sub) = 0;

        /**
         * @brief 设置是否默认订阅视频流
         * @param sub 是否默认订阅视频流
         - true:(Default)默认订阅视频流
         - false:默认不订阅视频流
         * @return
         - 0:设置成功
         - <0:设置失败
         * @note
         - 入会前入会后均可调用；
         - 如果在加入频道前调用 SetDefaultSubscribeAllRemoteVideoStreams (false)，则入会后默认不再订阅任何视频流；
         - 如果在加入频道后调用 SetDefaultSubscribeAllRemoteVideoStreams (false)，默认不再订阅设置后加入频道的用户的视频流；
         - 不管是否默认订阅，都可以调用 {@link AliEngine::SubscribeRemoteVideoStream}，对指定的用户进行订阅或取消订阅操作；
         - 订阅行为统一受到 {@link AliEngine::SubscribeAllRemoteVideoStreams} 这个总开关控制，假设 {@link AliEngine::SubscribeAllRemoteVideoStreams} 设置为false，则订阅全部关闭，其他启动行为全部不生效；
         */
        virtual int SetDefaultSubscribeAllRemoteVideoStreams(bool sub) = 0;
      
        /**
         * @brief 停止/恢复订阅所有远端视频流
         * @param sub 是否订阅所有远端视频流
         - true:订阅所有用户的视频流
         - false:停止订阅所有用户的视频流
         * @return
         - 0:设置成功
         - <0:设置失败
         * @note
         - 入会前入会后均可以调用
         - 如果设置了 SubscribeAllRemoteVideoStreams(false)，后面调用 {@link SetDefaultSubscribeAllRemoteVideoStreams} 和 {@link SubscribeRemoteVideoStream} 都不会生效；
         */
        virtual int SubscribeAllRemoteVideoStreams(bool sub) = 0;

        /**
         * @brief 停止/恢复订阅远端用户的视频流
         * @param uid userId，从App server分配的唯一标示符
         * @param track 视频流类型
         - AliEngineVideoTrackNo:无效参数，设置不会有任何效果
         - AliEngineVideoTrackCamera:相机流
         - AliEngineVideoTrackScreen:屏幕共享流
         - AliEngineVideoTrackBoth:相机流和屏幕共享流
         * @param sub 是否订阅远端用户的视频流
         - true:订阅指定用户的视频流
         - false:停止订阅指定用户的视频流
         * @return
         - 0:设置成功
         - <0:设置失败
         * @note
         - 如果之前有调用过 {@link AliEngine::SubscribeAllRemoteVideoStreams(false)} 停止订阅所有远端视频，则此接口调用无效；
         - {@link AliEngine::SubscribeAllRemoteVideoStreams} 是全局控制，SubscribeRemoteVideoStream 是单独控制。
         */
        virtual int SubscribeRemoteVideoStream(const char* uid, AliEngineVideoTrack track, bool sub) = 0;
 
        /**
         * @brief 设置视频流属性
         * @param videoTrack 视频流类型，详细见{@link AliEngineVideoTrack}
         * @param attr 视频流属性
         * @return
         * - 0 : 成功
         * - < 0 : 失败
         * @note 已废弃使用。
         */
        virtual int SetPublishVideoStreamAttribute(AliEngineVideoTrack videoTrack, const char* attr) = 0;

        /**
         * @brief 设置本地播放的指定远端用户音量
         * @param uid User ID。从App server分配的唯一标示符
         * @param volume 播放音量，取值范围:[0, 100]，0:静音，100:原始音量
         * @return 0表示成功，非0表示失败
         */
        virtual int SetRemoteAudioVolume(const char *uid,
                                           int volume) = 0;
        
        /**
         * @brief 停止/恢复远端的音频播放
         * @param uid User ID，从App server分配的唯一标示符
         * @param mute true表示停止播放；false表示恢复播放
         * @return 0为成功，非0失败
         */
        virtual int MuteRemoteAudio(const char *uid,
                                    bool mute) = 0;
        
        /**
         * @brief 停止/恢复远端所有的音频播放
         * @param mute true表示停止播放；false表示恢复播放
         * @return 0为成功，非0失败
         */
        virtual int MuteAllRemoteAudio(bool mute) = 0;
        
        /**
         * @brief 停止/恢复远端所有的视频渲染
         * @param mute true表示停止渲染，所有视频为黑帧；false表示恢复渲染
         * @return 0为成功，非0失败
         */
        virtual int MuteAllRemoteVideo(bool mute) = 0;
        
        /**
         * @brief 添加水印
         * @details SDK提供了添加水印的功能，适用于推送屏幕流或者相机流场景
         * @param track 视频流类型，只支持{@link AliEngineVideoTrackCamera}和{@link AliEngineVideoTrackScreen}
         * @param imageUrl 水印图片路径
         * @param options 水印配置，详细见{@link AliEngineWaterMarkConfig}
         * @return 
         * - 0 : 成功
         * - -1 : 失败
         * @note 目前水印图片仅仅支持png格式
         */
        virtual int AddVideoWatermark(AliEngineVideoTrack track,
                                      const char* imageUrl,
                                      const AliEngineWaterMarkConfig &options) = 0;
        
        /**
         * @brief 设置上行弱网替代图片
         * @param image_url 图片路径
         * @return 0:成功，-1:失败
        */
        virtual int SetPublishImage(const char* image_url) = 0;
        /**
         * @brief 清理水印
         * @details SDK提供了清理水印的功能，适用于推送屏幕流或者相机流场景
         * @param track 视频流类型，只支持{@link AliEngineVideoTrackCamera}和{@link AliEngineVideoTrackScreen}
         * @return 
         * - 0 : 成功
         * - -1 : 失败
         */
        virtual int ClearVideoWatermark(AliEngineVideoTrack track) = 0;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
        /**
         * @brief 设置默认音频输出是否从扬声器出声，默认从扬声器出声
         * @param defaultToSpeakerphone true:扬声器模式(默认扬声器)；false:听筒模式
         * @return 0表示Success 非0表示Failure
         */
        virtual int SetDefaultAudioRouteToSpeakerphone(bool defaultToSpeakerphone) = 0;

        /**
         * @brief 设置音频输出为听筒还是扬声器
         * @param enable true:扬声器模式；false:听筒模式(默认听筒)
         * @return 0表示Success 非0表示Failure
         */
        virtual int EnableSpeakerphone(bool enable) = 0;

        /**
         * @brief 获取当前音频输出为听筒还是扬声器
         * @return 0为成功，非0失败
         */
        virtual bool IsEnableSpeakerphone() = 0;
#endif

        /**
         * @brief 设置录音音量
         * @param volume   [0 400],0:静音，>100:放大音量，<100:减小音量
         * @return 0为成功，非0失败
         */
        virtual int SetRecordingVolume(int volume) = 0;

        /**
         * @brief 设置播放音量
         * @param volume   [0 400],0:静音，>100:放大音量，<100:减小音量
         * @return 0为成功，非0失败
         */
        virtual int SetPlayoutVolume(int volume) = 0;

        /**
         * @brief 设置音频Profile
         * @param audioProfile 音频采集/编码模式参数，参考AliEngineAudioProfile
         * @return audioScene 音频场景模式参数，参考AliEngineAudioScenario
        */
        virtual int SetAudioProfile(int audioProfile, int audioScene) = 0;
        
        /**
         * @brief 设置音量类型
         * @param type 音量类型
         * @return 0为成功，非0失败
        */
        virtual int SetDeviceVolumeType(int type) = 0;

#if (defined(__APPLE__) && TARGET_OS_IOS)
        /**
         * @brief 设置SDK对AVAudioSession的控制权限
         * @return 0为成功，非0失败
         */
        virtual int SetAudioSessionOperationRestriction(AliEngineAudioSessionOperationRestriction restriction) = 0;
#endif

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
        /**
         * @brief 切换前后摄像头
         * @return 0为成功，非0失败
         */
        virtual int SwitchCamera() = 0;
        
        /**
         * @brief 获取当前摄像头方向
         * @return 0为成功，非0失败
         */
        virtual AliEngineCameraDirection GetCurrentCameraDirection() = 0;

        /**
         * @brief 设置摄像头缩放比例
         * @param zoom   zoom的级别
         * @return 0为成功，非0失败
         */
        virtual int SetCameraZoom(float zoom) = 0;

        /**
         * @brief 设置摄像头闪光灯是否打开
         * @param flash  是否允许闪光灯
         * @return 0为成功，非0失败
         */
        virtual int SetCameraFlash(bool flash) = 0;
        
        /**
         * @brief 摄像头是否支持手动聚焦
         * @return true为支持，false为不支持
         */
        virtual bool IsCameraFocusPointSupported() = 0;

        /**
         * @brief 摄像头是否支持设置曝光区域
         * @return true为支持，false为不支持
         */
        virtual bool IsCameraExposurePointSupported() = 0;

        /**
         * @brief 设置摄像头手动聚焦
         * @param pointX   聚焦点x坐标
         * @param pointY   聚焦点y坐标
         * @return 0为成功，非0失败
         */
        virtual int SetCameraFocusPoint(float pointX, float pointY) = 0;

        /**
         * @brief 设置摄像头曝光点
         * @param pointX   聚焦点x坐标
         * @param pointY   聚焦点y坐标
         * @return 0为成功，非0失败
         */
        virtual int SetCameraExposurePoint(float pointX, float pointY) = 0;

        /**
         * @brief 摄像头是否支持人脸聚焦
         * @return ture表示支持 false表示不支持
         */
        virtual bool IsCameraAutoFocusFaceModeSupported() = 0;

        /**
         * @brief 设置摄像头人脸对焦
         * @param enable   true: 开启; false:关闭
         * @return ture表示成功 false表示失败
         */
        virtual bool SetCameraAutoFocusFaceModeEnabled(bool enable) = 0;
#endif

        /**
         * @brief 开启音频采集
         * @note 此接口可以控制提前打开音频采集，如果不设置，则SDK会在合适的时机在打开音频采集
         * @note 调用此接口后，离会后采集设备保持开启状态
         * @return 0为成功，非0失败
         */
        virtual int StartAudioCapture() = 0;
        
        /**
         * @brief 开启音频采集
         * @note 此接口可以控制提前打开音频采集，如果不设置，则SDK会在合适的时机在打开音频采集
         * @param keepAlive true: 离会后采集设备保持开启状态；false: 离会后采集设备关闭
         * @return 0为成功，非0失败
         */
        virtual int StartAudioCapture(bool keepAlive) = 0;
        
        /**
         * @brief 关闭音频采集
         * @note 此接口可以控制关闭音频采集，与startAudioCapture对应
         * @note 调用此接口后，入会后、离会再入会，采集设备保持关闭状态
         * @return 0为成功，非0失败
         */
        virtual int StopAudioCapture() = 0;
        
        /**
         * @brief 开启音频播放设备
         * @return 0为成功，非0失败
         */
        virtual int StartAudioPlayer() = 0;
        
        /**
         * @brief 关闭音频播放
         * @return 0为成功，非0失败
         */
        virtual int StopAudioPlayer() = 0;
        
        /**
         * @brief 开启本地音频流量控制
         * @param enable true表示开启,false表示关闭
         * @note 推流之前调用有效。
         * @note 开启语音活动检测可以在检测到没有语音的情况下，发送字节数减少，节省用户流量。
         * @return 0表示Success 非0表示Failure
         */
        virtual int EnableAudioDTX(bool enable) = 0;
        
        /**
         * @brief 开启本地音频流量控制
         * @param enable true表示开启,false表示关闭
         * @note 推流之前调用有效。
         * @note 开启语音活动检测可以在检测到麦克风静音或者关闭麦克风时停止发送音频包。
         * @return 0表示Success 非0表示Failure
         */
        virtual int EnableAudioAMD(bool enable) = 0;
        
        /**
         * @brief 开启智能降噪
         * @note 此接口可以通话过程中控制打开智能降噪功能
         * @return 0表示Success 非0表示Failure
         */
        virtual int StartIntelligentDenoise() = 0;

        /**
         * @brief 关闭智能降噪
         * @note 此接口可以通话过程中控制关闭智能降噪功能
         */
        virtual void StopIntelligentDenoise() = 0;

        /**
         * @brief 启用音乐模式
         * @param enable 是否启用音乐模式
         * @return 返回0为成功，其他返回错误码
         */
        virtual int EnableMusicMode(bool enable) = 0;
        
        /**
         * @brief 获取远端在线用户列表
         * @param userList 当前频道内所有在线用户userid列表
         * @note 若当前频道ChannelProfile设置为{@link AliEngineInteractiveLive}模式，只有设置角色为{@link AliEngineClientRoleInteractive}的用户为在线用户，本方法不返回角色为{@link AliEngineClientRoleLive}的用户
         */
        virtual void GetOnlineRemoteUsers(StringArray &userList) = 0;
        
        /**
         * @brief 查询远端用户的各种状态
         * @param uid        User ID。从App server分配的唯一标示符
         * @param dict       App提供的容器，用于存放用户数据
         */
        virtual int GetUserInfo(const char *uid,
                                Dictionary &dict) = 0;
        
        /**
         * @brief 查询是否设置推送视频流
         * @return
         - true: 已设置推送
         - false: 未设置推送
         * @note SDK默认设置推送视频流，如果需要取消推送视频流，可以通过{@link PublishLocalVideoStream}方法设置为不推送
         */
        virtual bool IsLocalVideoStreamPublished() = 0;
        
        /**
         * @brief 查询是否设置推送屏幕分享
         * @return
         - true: 已设置推送
         - false: 未设置推送
         * @note SDK默认设置不推送屏幕分享，如果需要推送屏幕共享，可以通过{@link StartScreenShareByDesktopId}, {@link StartScreenShareByScreenRegion} 或 {@link StartScreenShareByWindowId}方法开启屏幕共享推送
         */
        virtual bool IsScreenSharePublished() = 0;
        
        /**
         * @brief 查询是否设置推送音频流
         * @return
         - true: 已设置推送
         - false: 未设置推送
         * @note SDK默认设置推送音频流，如果需要取消推送音频流，可以通过{@link PublishLocalAudioStream}方法设置为不推送
         */
        virtual bool IsLocalAudioStreamPublished() = 0;

        /**
         * @brief 判断用户是否在线
         * @param uid User ID，从App server分配的唯一标示符。不可为NULL
         * @return true表示在线，false表示不在线
         */
        virtual bool IsUserOnline(const char *uid) = 0;
        
        /**
         * @brief 检查当前是否纯音频模式
         * @return true纯音频模式；false音视频模式
         */
        virtual bool IsAudioOnlyMode() = 0;
        
        /**
         * @brief 检查当前是否在频道中
         * @return true表示加入了频道；false表示不在频道中
         */
        virtual bool IsInCall() = 0;
        
        /**
         * @brief 检查当前是否打开摄像头
         * @return
         * - true: 表示已开启
         * - false: 表示未开启
         * @note 该接口用于检查当前camera的状态
         */
        virtual bool IsCameraOn() = 0;
        
        /**
         * @brief 获取当前网络链接状态
         * @return 当前链接状态, 参考{@link AliEngineConnectionStatus}
         * @note 网络链接状态发生变化时，SDK会通过{@link OnConnectionStatusChange}回调通知
         * @note 入会前调用此接口，均返回状态AliEngineConnectionDisconnected
         */
        virtual AliEngineConnectionStatus GetCurrentConnectionStatus() = 0;

        /**
         * @brief 设置音量回调频率和平滑系数
         * @param interval 时间间隔，单位毫秒，最小值不得小于10ms, 建议设置300-500ms, <= 0表示不启用音量提示和说话人提示功能
         * @param smooth 平滑系数，数值越大平滑程度越高，反之越低，实时性越好，建议设置3，范围[0, 9];
         * @param reportVad 说话人检测开关，1：开启，通过onAudioVolumeCallback接口回调每一个说话人的状态, 0:关闭
         * @return 0:成功，<0:方法调用失败
         */
        virtual int EnableAudioVolumeIndication(int interval, int smooth, int reportVad) = 0;

        /**
         * @brief 设置变声音效模式
         * @param mode 模式值，参看对应枚举类型
         * @return 0表示Success 非0表示Failure
         */
        virtual int SetAudioEffectVoiceChangerMode(const AliEngineAudioEffectVoiceChangerMode &mode) = 0;

        /**
         * @brief 设置变调参数
         * @param value 值，范围[0.5, 2.0], 默认1.0表示音调不变。
         * @return 0表示Success 非0表示Failure
         */
        virtual int SetAudioEffectPitchValue(double value) = 0;

        /**
         * @brief 设置混响音效模式
         * @param mode 类型
         * @return 0：成功  其他：失败
         */
        virtual int SetAudioEffectReverbMode(const AliEngineAudioEffectReverbMode& mode) = 0;

        /**
         * @brief 设置混响音效类型和具体参数
         * @param type 类型; value 具体参数值
         * @return 0：成功  其他：失败
         */
        virtual int SetAudioEffectReverbParamType(const AliEngineAudioEffectReverbParamType& type,
                                                  float value) = 0;

#if defined(__ANDROID__) || defined(__APPLE__) || defined(_WIN32)
        /**
         * @brief 开始混音
         * @param onlyLocalPlay 是否只本地播放
         * @param replaceMic 是否替换掉MIC
         * @param loopCycles 循环次数(可以设置-1或者正整数)
         * @return 返回0为成功，其他返回错误码
         */
        virtual int StartAudioAccompany(const char *filePath,
                                        bool onlyLocalPlay,
                                        bool replaceMic,
                                        int loopCycles) = 0;
        
        /**
         * @brief 停止混音
         * @return 返回0为成功，其他返回错误码
         */
        virtual int StopAudioAccompany() = 0;

        /**
         * @brief 设置混音音量
         * @param volume 混音音量 0~100
         * @return 返回0为成功，其他返回错误码
         * @note 设置音量需要在startAudioAccompany后才能生效
         */
        virtual int SetAudioAccompanyVolume(int volume) = 0;

        /**
         * @brief 设置混音之后推流出去的音量
         * @param volume 混音音量 0~100
         * @return 返回0为成功，其他返回错误码
         * @note 设置音量需要在startAudioAccompany后才能生效
         */
        virtual int SetAudioAccompanyPublishVolume(int volume) = 0;

        /**
         * @brief 获取推流出去的混音音量
         * @return 返回0为成功，其他返回错误码
         */
        virtual int GetAudioAccompanyPublishVolume() = 0;

        /**
         * @brief 设置混音之后本地播放的音量
         * @param volume 混音音量 0~100
         * @return 返回0为成功，其他返回错误码
         * @note 设置音量需要在startAudioAccompany后才能生效
         */
        virtual int SetAudioAccompanyPlayoutVolume(int volume) = 0;

        /**
         * @brief 获取混音本地播放的音量
         * @return 返回0为成功，其他返回错误码
         */
        virtual int GetAudioAccompanyPlayoutVolume() = 0;

        /**
         * @brief 暂停混音
         * @return 返回0为成功，其他返回错误码
         */
        virtual int PauseAudioAccompany() = 0;

        /**
         * @brief 重新开始混音
         * @return 返回0为成功，其他返回错误码
         */
        virtual int ResumeAudioAccompany() = 0;

        /**
         * @brief 获取伴奏文件时长, 单位为ms
         * @return 返回0为成功，其他返回错误码
         * @note OnAudioPlayingStateChanged回调播放状态为AliEngineAudioPlayingStarted后获取伴奏时长有效
         */
        virtual int GetAudioAccompanyDuration() = 0;

        /**
         * @brief 获取音乐文件播放进度，单位为毫秒。
         * @return 返回0为成功，其他返回错误码
         */
        virtual int GetAudioAccompanyCurrentPosition() = 0;

        /**
         * @brief 设置音频文件的播放位置
         * @param pos 进度条位置，单位为毫秒
         * @return 进度条位置，单位为毫秒
         */
        virtual int SetAudioAccompanyPosition(int pos) = 0;

        /**
         * @brief 预加载音效文件
         * @param soundId 用户给该音效文件分配的ID
         * @param filePath 音效文件路径
         * @return 返回0为成功，其他返回错误码
         */
        virtual int PreloadAudioEffect(unsigned int soundId,
                                       const char *filePath) = 0;

        /**
         * @brief 删除预加载的音效文件
         * @param soundId 用户给该音效文件分配的ID
         * @return 返回0为成功，其他返回错误码
         */
        virtual int UnloadAudioEffect(unsigned int soundId) = 0;

        /**
         * @brief 开始播放音效
         * @param soundId 用户给该音效文件分配的ID
         * @param filePath 文件路径
         * @param cycles 循环次数(可以设置-1或者正整数)
         * @param publish 是否发布
         * @return 返回0为成功，其他返回错误码
         */
        virtual int PlayAudioEffect(unsigned int soundId,
                                    const char *filePath,
                                    int cycles,
                                    bool publish) = 0;

        /**
         * @brief 停止播放音效
         * @param soundId 用户给该音效文件分配的ID
         * @return 返回0为成功，其他返回错误码
         */
        virtual int StopAudioEffect(unsigned int soundId) = 0;
        
        /**
         * @brief 停止播放所有音效
         * @return 返回0为成功，其他返回错误码
        */
        virtual int StopAllAudioEffects() = 0;

        /**
         * @brief 设置音效推流音量
         * @param soundId 用户给该音效文件分配的ID
         * @param volume 混音音量 0~100
         * @return 返回0为成功，其他返回错误码
         */
        virtual int SetAudioEffectPublishVolume(unsigned int soundId, int volume) = 0;

        /**
         * @brief 获取推流音效音量
         * @param soundId 用户给该音效文件分配的ID
         * @return 返回0~100为成功，其他返回错误码
         */
        virtual int GetAudioEffectPublishVolume(unsigned int soundId) = 0;

        /**
         * @brief 设置音效本地播放音量
         * @param soundId 用户给该音效文件分配的ID
         * @param volume 混音音量 0~100
         * @return 返回0为成功，其他返回错误码
         */
        virtual int SetAudioEffectPlayoutVolume(unsigned int soundId, int volume) = 0;

        /**
         * @brief 获取音效本地播放音量
         * @param soundId 用户给该音效文件分配的ID
         * @return 返回0~100为成功，其他返回错误码
         */
        virtual int GetAudioEffectPlayoutVolume(unsigned int soundId) = 0;
        
        /**
         * @brief 设置所有音效推流音量
         * @param volume 混音音量 0~100
         * @return 返回0为成功，其他返回错误码
        */
        virtual int SetAllAudioEffectsPublishVolume(int volume) = 0;
        /**
         * @brief 设置所有音效本地播放音量
         * @param volume 混音音量 0~100
         * @return 返回0为成功，其他返回错误码
        */
        virtual int SetAllAudioEffectsPlayoutVolume(int volume) = 0;

        /**
         * @brief 暂停音效
         * @param soundId 用户给该音效文件分配的ID
         * @return 返回0为成功，其他返回错误码
         */
        virtual int PauseAudioEffect(unsigned int soundId) = 0;
        
        /**
         * @brief 暂停所有音效
         * @return 返回0为成功，其他返回错误码
         */
        virtual int PauseAllAudioEffects() = 0;

        /**
         * @brief 重新开始播放音效
         * @@param soundId 用户给该音效文件分配的ID
         * @return 返回0为成功，其他返回错误码
         */
        virtual int ResumeAudioEffect(unsigned int soundId) = 0;
        
        /**
         * @brief 重新开始播放所有音效
         * @return 返回0为成功，其他返回错误码
         */
        virtual int ResumeAllAudioEffects() = 0;

#endif
        
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
        /**
         * @brief 启用耳返
         * @param enable 是否启用耳返
         * @return 返回0为成功，其他返回错误码
         */
        virtual int EnableEarBack(bool enable) = 0;

        /**
         * @brief 设置耳返音量
         * @param volume 音量 0~100 默认100
         * @return 返回0为成功，其他返回错误码
         */
        virtual int SetEarBackVolume(int volume) = 0;
#endif
        /**
         * @brief 美颜功能是否有效
         */
        virtual bool IsBeautifierAvailable() = 0;
        
        /**
         * @brief 美颜功能是否开启
         */
        virtual bool IsBeautifierEnabled() = 0;

        /**
         * @brief 开启或关闭美颜功能，并设置美颜效果参数
         * @param enable
         * - true 开启美颜功能
         * - false 关闭美颜功能
         * @param config 美颜效果参数, 详细定义见{@link AliEngineBeautyConfig}
         * @return
         * - 0 : 成功
         * - < 0 : 失败
         */
        virtual int SetBeautyEffect(bool enable, const AliEngineBeautyConfig &config) = 0;
        
        /**
         * @brief 视频截图功能
         * @param userId 用户ID， userId 为""代表本地用户
         * @param trackType 视频流类型，只支持{@link AliEngineVideoTrackCamera}和{@link AliEngineVideoTrackScreen}
         * @return
         * - 0 : 仅代表调用该接口成功，是否获取到截图画面，详细见{@link AliEngineEventListener::onSnapshotComplete}
         * - < 0 : 失败
         * @note 视频截图功能为异步接口, 通过监听{@link AliEngineEventListener::onSnapshotComplete}回调获取当前截图画面。
         */
        virtual int SnapshotVideo(const String& userId, const AliEngineVideoTrack &trackType) = 0;

        /**
         * @brief 开始录制
         * @details SDK提供了屏录录制的功能，可以录制本地或远端的音频流、视频流、相机流
         * @param recordType 录制类型, 详细定义见{@link AliEngineRecordType}
         * @param recordFormat 录制文件格式, 详细定义见{@link AliEngineRecordFormat}
         * @param filePath 文件路径
         * @param audioConfig 音频设置, 详细定义见{@link AliEngineRecordAudioConfig}
         * @param videoConfig 视频设置, 详细定义见{@link AliEngineRecordVideoConfig}
         * @param isFragment 是否支持mp4内部分段，只在录制mp4时有效
         * @return
         * - true : 成功
         * - false : 失败
         * @note 此接口为旧接口，新接口为{@link StartRecord(const char* filePath, const AliEngineRecordVideoLayout& layout)}
         */
        virtual bool StartRecord(AliEngineRecordType recordType,
                                 AliEngineRecordFormat recordFormat,
                                 const char * filePath,
                                 AliEngineRecordAudioConfig& audioConfig,
                                 AliEngineRecordVideoConfig& videoConfig,
                                 bool isFragment) = 0;
        
        /**
         * @brief 更新录制内容信息
         * @details SDK提供了更新录制内容信息的功能,用于实时更新录制模板内容设置
         * @param layout 录制视频内容及布局, 详细定义见{@link AliEngineRecordVideoLayout}
         * @return
         * - true : 成功
         * - false : 失败
         * @note UpdateRecordLayout更新录制内容信息应该在录制过程中调用
         */
        virtual bool UpdateRecordLayout(AliEngineRecordVideoLayout& layout) = 0;
        
        /**
         * @brief 添加录制模板
         * @details SDK提供了添加录制模板的功能,用于添加录制模板
         * @param rTemplate 录制模板, 详细定义见{@link AliEngineRecordTemplate}
         * @return
         * - 0 : 成功
         * - -1 : 失败
         * @note AddRecordTemplate添加录制模板必须在StartRecord之前调用
         */
        virtual int AddRecordTemplate(const AliEngineRecordTemplate& rTemplate) = 0;

        /**
         * @brief 开始录制
         * @details SDK提供了屏录录制的功能，可以录制本地或远端的音频流、视频流、相机流，窗口布局设置参考{@link AliEngineRecordVideoLayout}
         * @param filePath 文件路径
         * @param layout 视频窗口布局设置, 详细定义见{@link AliEngineRecordVideoLayout}
         * @return
         * - 0 : 成功
         * - -1 : 失败
         * @note StartRecord之前调用必须先调用AddRecordTemplate添加录制模板
         */
        virtual int StartRecord(const char* filePath, const AliEngineRecordVideoLayout& layout) = 0;
        
        /**
         * @brief 暂停录制
         * @details SDK提供了暂停录制的功能
         * @return
         * - true : 成功
         * - false : 失败
         */
        virtual bool PauseRecord()  = 0;
        
        /**
         * @brief 重新开始录制
         * @details SDK提供了重新开始录制的功能
         * @return
         * - true : 成功
         * - false : 失败
         */
        virtual bool ResumeRecord()  = 0;
        
        /**
         * @brief 停止录制
         * @details SDK提供了停止录制的功能
         * @return
         * - true : 成功
         * - false : 失败
         */
        virtual bool StopRecord() = 0;

        /**
         * @brief 开始网络质量探测
         * @details 网络质量探测需要在未入会 {@link JoinChannel} 情况下调用，探测结果在 {@link AliEngineEventListener::OnLastmileDetectResultWithQuality} 中回调
         * @return
         * - 0: 成功
         * - <0: 失败
         */
        virtual int StartLastmileDetect() = 0;

        /**
         * @brief 停止网络质量探测
         * @return
         * - 0: 成功
         * - <0: 失败
         */
        virtual int StopLastmileDetect() = 0;

        /**
         * @deprecated
         * @brief 开始低延时互动直播拉流
         * @details 该方法仅在低延迟互动模式 {@link AliEngineInteractiveWithLowLatencyLive } 下，角色为观众 {@link AliEngineClientRolelive } 时调用有意义
         * @param authInfo 入会鉴权信息
         * @note 调用该方法后，会触发 {@link AliEngineEventListener::OnStartLiveStreamingResult} 回调
         * @note 该接口已废弃
         */
        virtual void StartLiveStreaming(const AliEngineAuthInfo &authInfo) = 0;

        /**
         * @deprecated
         * @brief 停止低延时互动直播拉流
         * @return
         * - 0: 成功
         * - <0: 失败
         * @note 该方法仅在低延迟互动模式下，角色为观众时调用有意义
         * @note 停止直播拉流后如需再次进入，需要先destroy销毁SDK，重新创建后再次进入
         * @note 该接口已废弃
         */
        virtual int StopLiveStreaming() = 0;
        
        /**
         * @deprecated
         * @brief 设置低延时互动直播拉流窗口及渲染参数
         * @param config 渲染参数，包含了窗口以及渲染方式
         * @return 
         * - 0: 成功
         * - <0: 失败
         * @note 该接口已废弃
         */
        virtual int SetLiveStreamingViewConfig(AliEngineVideoCanvas& config) = 0;

        /**
         * @brief 开启旁路直播
         * @details SDK提供了开启旁路直播的功能，可以把实时音视频流经过混流、混音处理转为标准直播流并推送至指定CDN供应商
         * @param streamURL 推流地址
         * @param transcoding 推流所需参数, 详细定义见{@link AliEngineLiveTranscodingParam}
         * @return
         * - 0 : 成功
         * - 非0 : 失败
         *      ERR_INNER(-1) : SDK内部错误，可能的情况为SDK未初始化或者SDK销毁后调用
         *      其他 : 返回值参考官网错误码
         */
        virtual int StartPublishLiveStream(const String& streamURL, const AliEngineLiveTranscodingParam &transcoding) = 0;
        
        /**
         * @brief 更新旁路直播相关参数
         * @details SDK提供了更新旁路直播的功能，用于实时更新旁路直播参数
         * @param streamURL 推流地址
         * @param transcoding 推流所需参数, 详细定义见{@link AliEngineLiveTranscodingParam}
         * @return
         * - 0 : 成功
         * - 非0 : 失败
         *      ERR_INNER(-1) : SDK内部错误，可能的情况为SDK未初始化或者SDK销毁后调用
         *      其他 : 返回值参考官网错误码
         */
        virtual int UpdatePublishLiveStream(const String& streamURL, const AliEngineLiveTranscodingParam &transcoding) = 0;
        
        /**
         * @brief 停止旁路直播
         * @details SDK提供了停止旁路直播的功能
         * @param streamURL 推流地址
         * @return
         * - 0 : 成功
         * - 非0 : 失败
         *      ERR_INNER(-1) : SDK内部错误，可能的情况为SDK未初始化或者SDK销毁后调用
         *      其他 : 返回值参考官网错误码
         */
        virtual int StopPublishLiveStream(const String& streamURL) = 0;

        /**
         * @brief 获得旁路直播状态
         * @param streamURL 推流地址
         * @return 返回AliEngineLiveTranscodingState
        */
        virtual AliEngineLiveTranscodingState GetPublishLiveStreamState(const String& streamURL) = 0;

        /**
         * @brief 更新直播拉流窗口及渲染参数
         * @param renderConfig 包含了窗口以及渲染方式
         * @return 返回0为成功，其他返回错误码
         */
        virtual int UpdateLiveStreamingViewConfig(AliEngineVideoCanvas& renderConfig) = 0;
        
        /**
         * @brief 发送媒体扩展信息
         * @details SDK提供了发送和接收媒体扩展信息的功能，接收端参考 {@link AliEngineEventListener::OnMediaExtensionMsgReceived}，使用场景：
         * - 使用媒体扩展信息传递时间戳，计算端到端的网络延迟，或者跟自身其他业务做数据同步
         * - 使用媒体扩展信息传递位控制信息。目前可以传递8 Byte数据，即64位，每一位或几位可以表示控制信息，用于自身业务上的指令传输
         * 
         * @param message 扩展信息内容, 长度限制为最大8字节
         * @param length 扩展信息长度
         * @param repeatCount 重复次数，代表消息冗余度，用于防止网络丢包导致的消息丢失
         * @return
         * - 0: 成功
         * - <0: 失败
         *      - ERR_INNER(-1): SDK内部错误，可能的情况为SDK未初始化或者SDK销毁后调用
         * 
         * @note 使用媒体扩展信息时需要复用音视频数据通道，因此必须控制自定义消息的发送频率和消息数据长度，使用限制如下：
         * - 每秒最多发送30条消息
         * - 为了不影响媒体数据的传输质量，自定义消息体长度限制为8 Byte，可以用来传输时间戳，位控制信息等
         * - sendMediaExtensionMsg函数中repeatCount参数为自定义消息冗余度，若大于1，则会发送多次，防止网络丢包导致的消息丢失，此时房间里的其他人也会收到多次相同的消息，需要去重
         * - 发送的自定义消息，在旁路直播时，房间里的订阅者也一样会收到
         * - 目前H5端不支持发送和接收媒体扩展信息
         */
        virtual int SendMediaExtensionMsg(unsigned char *message, unsigned int length, int repeatCount) = 0;

        /**
         * @brief 根据桌面Id进行屏幕分享
         * @param desktopId 桌面Id(可通过GetScreenShareSourceInfo接口获取)
         * @param config 屏幕分享配置
         * @return 成功返回0，失败返回错误码
         * @note 配置指定区域分享时，分享区域最小分辨率为16 x 16，设置区域小于最小分辨率时重置为最小分辨率
         * @note 配置指定区域分享时，设置分享区域超过实际桌面分辨率时，将分享整个桌面
        */
        virtual int StartScreenShareByDesktopId(unsigned int desktopId, const AliEngineScreenShareConfig& config) = 0;

#if defined(_WIN32)
        /**
         * @brief 根据屏幕区域进行屏幕分享
         * @param screenRegion 指定要共享的屏幕相对于虚拟屏幕的位置
         * @param config 屏幕分享配置
         * @return 成功返回0，失败返回错误码
         * @note 本方法仅适用于桌面共享，设置窗口共享请使用StartScreenShareByWindowId接口
         * @note 配置指定区域分享时，分享区域最小分辨率为16 x 16，设置区域小于最小分辨率时重置为最小分辨率
         * @note 配置指定区域分享时，设置分享区域超过实际桌面分辨率时，将分享整个桌面
         * @note 关于虚拟屏幕坐标请参考https://docs.microsoft.com/en-us/windows/win32/gdi/the-virtual-screen
        */
        virtual int StartScreenShareByScreenRegion(const AliEngineScreenShareRegion& screenRegion, const AliEngineScreenShareConfig& config) = 0;
#endif

        /**
         * @brief 根据窗口id进行屏幕分享
         * @param windowId 窗口id(可通过GetScreenShareSourceInfo接口获取)
         * @param config 屏幕分享配置
         * @return 成功返回0，失败返回错误码
        */
        virtual int StartScreenShareByWindowId(unsigned int windowId, const AliEngineScreenShareConfig& config) = 0;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
        /**
         * @brief 开始屏幕分享
         * @return 成功返回0，失败返回错误码
        */
        virtual int StartScreenShare() = 0;
#endif
        /**
         * @brief 停止屏幕分享
         * @return 成功返回0，失败返回错误码
        */
        virtual int StopScreenShare() = 0;

        /**
         * @brief 更新屏幕分享配置
         * @param config 屏幕分享配置
         * @return 成功返回0，失败返回错误码
        */
        virtual int UpdateScreenShareConfig(const AliEngineScreenShareConfig& config) = 0;

        /**
         * @brief 获取屏幕共享配置
         * @return =0表示成功， <0表示失败
        */
        virtual AliEngineScreenShareConfig GetScreenShareConfig() = 0;

        /**
         * @brief 获取屏幕分享源信息
         * @param[in] sourceType 屏幕分享类型
         * @return 返回屏幕共享源列表
         * @note 请在遍历完屏幕共享源列表后调用其release成员方法，由SDK内部释放相关资源
         */
        virtual AliEngineScreenSourceList* GetScreenShareSourceInfo(AliEngineScreenShareType sourceType) = 0;

        /**
         * @brief 获取当前屏幕共享源Id
         * @return 当前屏幕共享源Id
        */
        virtual unsigned int GetCurrentScreenShareSourceId() = 0;

        /**
         * @brief 获取当前屏幕共享源类型
         * @return 当前屏幕共享源类型
        */
        virtual AliEngineScreenShareType GetCurrentScreenShareSourceType() = 0;

        /**
         * @brief 获取屏幕分享桌面区域
         * @param[in] sourceId    屏幕分享数据源id
         * @param[in] sourceTitle 屏幕分享数据源名称
         * @param[out] region     屏幕区域信息
         * @return 0为成功，非0失败
         * @note 只针对AliEngineScreenShareDesktop
         */
        virtual int GetDesktopRegion(const String& sourceId, const String& sourceTitle, AliEngineScreenShareRegion& region) = 0;

        /**
         * @brief 更新滚动条坐标.
         * @param config 配置参数
         * @return 0 表示成功，1 表示失败
         */
        virtual int UpdateScrollView(const AliEngineScrollViewConfig &config) = 0;

        /**
         * @brief 开启/关闭系统声音采集推送
         * @param enable true为开启, false为关闭
         * @param path path为空，则采集整个系统的声音；path为exe程序路径，则启动此程序并采集其声音
         * @return =0表示成功， <0表示失败
         */
        virtual int EnableSystemAudioRecording(bool enable, const char *path = nullptr) = 0;

        /**
         * @brief 当前是否开启系统声音采集推送
         * @return 返回true为开启状态， false为关闭状态
         */
        virtual bool IsSystemAudioRecording() = 0;

        /**
         * @brief 设置系统声音采集推送音量
         * @param volume 设置音量
         * @return =0表示成功， <0表示失败
         */
        virtual int SetSystemAudioRecordingVolume(int volume) = 0;

        /**
         * @brief 获取当前设置系统声音采集推送音量
         * @return 系统音量
         * @note 需要开启系统声音采集推送后才能设置，否则设置失败
         */
        virtual int GetSystemAudioRecordingVolume() = 0;

        /**
         * @brief SDK问题反馈
         * @param uid 当前 uid(允许为空)
         * @param channelId 当前channel id(允许为空)
         * @param description 问题描述(支持中英文, 不允许为空)
         * @param type 问题类型
         * @param timeStamp 问题发生的时间戳(Unix时间戳，大致时间，无需特别精确，可以为0)
         */
        virtual void PostFeedback(const char *uid, const char *channelId, const char *description, const AliEngineFeedbackType type, long long timeStamp) = 0;
        
        /**
         * @brief 发送下行通道消息(反馈消息处理结果)
         * @param messageInfo 信息内容
         * @return
         * - 0: 成功
         * - <0: 失败
         * @note 接收到下行通道消息 {@link AliEngineEventListener::OnDownlinkMessageNotify} 后，使用该接口发送下行接收反馈消息
         * @note 已废弃使用
         * @deprecated
         */
        virtual int SendDownlinkMessageResponse(const AliEngineMessage &messageInfo) = 0;
  
        /**
         * @brief 开启跨频道转推
         * @param configuration 频道配置信息 {@link AliEngineChannelRelayConfiguration}
         * @return
         * - 0: 成功
         * - <0: 失败
         * @note 发起跨频道转推需要满足三个条件
         * - 会议模式为互动模式或者低延迟互动模式
         * - 必须是主播角色
         * - 必须在会议中
         */
        virtual int StartChannelRelay(const AliEngineChannelRelayConfiguration &configuration) = 0;

        /**
         * @brief 更新跨频道转推
         * @param configuration 频道配置信息 {@link AliEngineChannelRelayConfiguration}
         * @return
         * - 0: 成功
         * - <0: 失败
         */
        virtual int UpdateChannelRelay(const AliEngineChannelRelayConfiguration &configuration) = 0;

        /**
         * @brief 停止跨频道转推
         * @return
         * - 0: 成功
         * - <0: 失败
         */
        virtual int StopChannelRelay() = 0;

        /**
         *  @brief 刷新鉴权信息
         *  @details 该方法用于更新鉴权信息 {@link AliEngineAuthInfo} ，主要为了防止鉴权过期，导致推流失败，当我们收到 {@link AliEngineEventListener::OnAuthInfoWillExpire}回调时，应用应当更新鉴权信息
         *  @param authInfo 鉴权信息
         *  @return
         *  - 0: 成功
         *  - <0: 失败
         */
        virtual int RefreshAuthInfo(const AliEngineAuthInfo &authInfo) = 0;

        /**
         * @brief 发送上行通道消息
         * @param messageInfo 信息内容
         * @return
         * - 0: 成功
         * - <0: 失败
         * @note 使用该接口发送上行通道消息成功后，接收反馈消息见 {@link AliEngineEventListener::OnUplinkMessageResponse}
         * @note 已废弃使用
         * @deprecated
         */
        virtual int SendUplinkMessage(const AliEngineMessage &messageInfo) = 0;
        
        /**
         * @brief 创建一个AliEngineEngine子频道实例
         * @param extras 用于接收来自客户灰度下发的参数
         * @note 创建的子频道实例需要通过DestroyChannel进行释放
        */
        virtual AliEngine * CreateChannel(const char* extras) = 0 ;
        
        /**
         * @brief 销毁CreateChannel创建的子频道
         */
        virtual void DestroyChannel() = 0 ;
        
        /** plugin api*/
        /**
         * @brief 添加音视频处理算法插件
         * @param moduleName 插件包名
         * @param pluginName 插件类名
         * @param pluginType 插件类型
         * @param opType 调用init函数传入插件
         * @param option 通过init函数传入插件
         * @return return >0 为pluginID，return<0 Failure
        */
        virtual int EnablePlugin(const char* moduleName, const char* pluginName, unsigned int pluginType, unsigned int opType, const void* option) = 0;
        
        /**
         * @brief 移除音视频处理算法插件
         * @param pluginId 插件ID
         * @return return >0 为pluginID，return<0 Failure
        */
        virtual int RemovePlugin(unsigned int pluginId) = 0;
                 
        /**
         * @brief 设置插件参数
         * @param pluginId 插件ID,由 enablePlugin接口 返回
         * @param opType 参数
         * @param option 参数值
         * @return return = 0 Success
        */
        virtual int SetPluginOption(unsigned int pluginId, unsigned int opType, const void* option) = 0;
                 
        /**
         * @brief 获取插件设置
         * @param pluginId 插件ID,由 enablePlugin接口 返回
         * @param opType 参数
         * @param option 查找结果
         * @return return = 0 Success
        */
        virtual int GetPluginOption(unsigned int pluginId, unsigned int opType, void* option) = 0;
        
        /**
         * @brief 展示用户Debug数据
         * @param view 对外展示的View，由客户传入，显示样式由客户指定
         * @param showType 展示类型:0: 不显示 1.音频 2.视频 3.网络 4.全部；另外可以传入特殊的值来展示
         * @param uid 对应用户ID
         * @return return = 0 Success
        */
        virtual int ShowDebugView(void* view,const AliEngineShowDebugViewType showType,const char *uid) = 0;
        /**
         * @brief 开启/关闭虚拟背景替换功能：需要对应PluginBokeh 库添加
         * @param enable 是否开启
         * @param path 本地图片路径，支持 JPG，png 格式
         * @param model 背景图缩放模式，裁剪或缩放
         * @return 0 Success 非0 Failure
        */
        virtual int EnableBackgroundExchange(bool enable, const char* path,const AliEngineBokehScaleModel model) = 0;
        

        /**
         * @brief 开启/关闭虚拟背景虚化功能：需要对应PluginBokeh 库添加，背景替换与虚化不同时出现
         * @param enable 是否开启
         * @param degree  虚化程度 [0-100]
         * @return 0 Success 非0 Failure
        */
        virtual int EnableBackgroundBlur(bool enable, uint32_t degree) = 0;
        /**
         * @brief 开启/关闭内置加解密功能：需要在入会前调用
         * @param enable 是否开启
         * @return 0 Success 非0 Failure
        */
        virtual int EnableEncryption(bool enable) = 0;
    };
    /// The declarations listed above are subject to change without notice.
}

#endif /* engine_interface_h */
