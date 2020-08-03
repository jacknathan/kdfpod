//
//  KDFCreditcardsTool.h
//  KDFCreditcardsTool
//
//  Created by ChenYong on 2018/8/6.
//  Copyright © 2018 samoyed. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ErrorDefine.h"

typedef enum KDFServerMode {
    KDFServerModeProduct = 0,    //正式的生产环境，默认配置
    KDFServerModeStandTest,      //测试环境
    KDFServerModeDevelopment,    //开发环境
} KDFServerMode;

typedef void(^FinishHandlerBlock)(BOOL isSucceed, NSString *strErrorCode, NSString *strErrorInfo);

@interface KDFCreditcardsTool : NSObject

/**
 奖金比例 0~100
 */
@property (nonatomic, assign) float bonusRate;

/**
 分配给第三方的app key
 建议在App启动后, 在application:didFinishLaunchingWithOptions:中设置
 */
@property (nonatomic, copy) NSString *appKey;

/**
 分享给第三方
 建议在App启动后, 在application:didFinishLaunchingWithOptions:中设置
 */
@property (nonatomic, copy) NSString *isShare;


/**
 佣金的A/B方案对应页面显示类型
 建议在App启动后, 在application:didFinishLaunchingWithOptions:中设置
 */
@property (nonatomic, copy) NSString *showType;

/**
 分享佣金比例
 建议在App启动后, 在application:didFinishLaunchingWithOptions:中设置
 */
@property (nonatomic, copy) NSString *shareRate;

/**
 手机号
*/
@property (nonatomic, copy) NSString *mobile;

/**
 备用字段
*/
@property (nonatomic, copy) NSString *extend;


/**
 用于接收和处理用户在信用卡页面点击分享等的操作
 */
@property (nonatomic, copy) void(^userDidClickedHandler)(NSString *strAction, NSString *strParam);

/**
 用于处理用户的登录请求，登录成功后要调用loginSucceedHandler
 */
@property (nonatomic, copy) void(^userDidWantToLoginHandler)(dispatch_block_t loginSucceedHandler);

/**
 用于跳转到信用卡首页，将信用卡首页放在一个独立的tab中的App才需要设置该属性，便于SDK在部分页面直接切换到独立的信用卡首页
 */
@property (nonatomic, copy) dispatch_block_t jumpToCreditcardsHomeHandler;

/**
 设置SDK的使用环境，默认是正式的生产环境
 */
+ (void)setServerMode:(KDFServerMode)mode;

+ (KDFServerMode)serverMode;

+ (instancetype)sharedInstance;

+ (NSString *)currentH5Domain;

+ (void)setSDKLogHandler:(void(^)(NSString *strLog))handler;

/**
 查询当前用户是否已经登录
 @param strUserId 联合登录时你们用来生成当前用户的user token的user Id
 */
- (BOOL)hasLoginUser:(NSString *)strUserId;

/**
 登录指定用户
 同一时间只能有一个用户处于登录状态

 @param strLoginToken 用于联合登录的token，应该请求你们自己的后台获取
 @param finishHandler 登录完成的回调
 */
- (void)loginWithToken:(NSString *)strLoginToken finishHandler:(void(^)(BOOL bLoginSucceed, NSString *strErrorCode, NSString *strErrorInfo))finishHandler;

/**
 登录指定用户 新添mbile(手机号)字段
 同一时间只能有一个用户处于登录状态
 
 @param strLoginToken 用于联合登录的token，应该请求你们自己的后台获取
 @param mobile        手机号
 @param extend        备用字段
 @param finishHandler 登录完成的回调
 */
- (void)loginWithToken:(NSString *)strLoginToken mobile:(NSString *)mobile extend:(NSString *)extend finishHandler:(void(^)(BOOL bLoginSucceed, NSString *strErrorCode, NSString *strErrorInfo))finishHandler;

/**
 同一时间只能有一个用户处于登录状态
 
 @param userId        第三方用户id
 @param mobile        手机号
 @param publicKey     公钥
 @param finishHandler 登录完成的回调
 */
- (void)loginWithUserId:(NSString *)userId mobile:(NSString *)mobile publicKey:(NSString *)publicKey finishHandler:(FinishHandlerBlock)finishHandler;

/**
 当前用户退出登录
 */
- (void)logout;

/**
 直接得到信用卡首页，用于在tab中使用该页面，这是一个单例
 */
- (UIViewController *)creditcardsHomeTabPage;

/**
 自定义首页，用于在tab中使用该页面，这是一个单例
 */
- (UIViewController *)customHomeTabPage:(NSString *)urlStr;

/**
 打开信用卡首页
 */
- (BOOL)pushCreditcardsHomePageInNav:(UINavigationController *)navCtl;

/**
 打开提现页面
 */
- (BOOL)pushExtractPageInNav:(UINavigationController *)navCtl;

/**
 打开订单页面
 */
- (BOOL)pushOrdersPageInNav:(UINavigationController *)navCtl;

/**
 打开我的关注页面
 */
- (BOOL)pushCardsShopPageInNav:(UINavigationController *)navCtl;

/**
 打开银行卡管理页面
 */
- (BOOL)pushMyCardsPageInNav:(UINavigationController *)navCtl;

/**
 打开指定卡片的详情页面
 */
- (BOOL)pushDetailPageOfCard:(NSString *)strCardId inNav:(UINavigationController *)navCtl;

/**
 打开指定银行卡片列表或者指定卡片的详情页面
 BankID:银行ID
 CardId:卡片ID
 */
-(BOOL)toCardListOrDetailActivityWithBankID:(NSString *)BankID WithCardId:(NSString *)CardId inNav:(UINavigationController *)navCtl;
/**
 打开Html页面
 */
- (BOOL)pushHtmlWithUrlStr:(NSString *)urlStr inNav:(UINavigationController *)navCtl;

/**
 打开配置资源位
 */
- (BOOL)pushConfigureResourcesOfPosition:(NSString *)position inNav:(UINavigationController *)navCtl finishHandler:(FinishHandlerBlock)finishHandler;

/**
 车来了   打开配置资源位
 */
- (BOOL)pushConfigureResourcesOfPosition:(NSString *)position withUuid:(NSString *)UUID inNav:(UINavigationController *)navCtl finishHandler:(FinishHandlerBlock)finishHandler;

/**
 *   打开自定义页面
 *   @param userId         第三方用户id
 *   @param pathStr         路径
 *   @param navCtl         导航
 *   @param finishHandler  完成回调
 */
- (void)pushCustomPageWithUserId:(NSString *)userId pathStr:(NSString *)pathStr inNav:(UINavigationController *)navCtl finishHandler:(FinishHandlerBlock)finishHandler;

/**
 获取用户的订单列表
 
 每个订单的信息存储在一个字典中，字典中有以下key：
 id：信用卡记录ID
 bankCode：银行编码
 bankName：银行名称
 cardName：信用卡名称
 cardIcon：信用卡图标
 bankIcon：银行图标
 custNo：客户号
 custName：姓名
 applyStatus：申请状态:001-待查询，002-审核中，003-爬虫审核通过，004-爬虫审核拒绝
 applyDatetime：申请时间
 bonus：佣金奖励
 crawId：爬取Id

 @param finishHandler 获取结束的回调
 */
- (void)fetchUserOrderList:(void(^)(BOOL bSucceed, NSArray <NSDictionary *>*arrayOrderInfos, NSString *strErrorCode, NSString *strErrorInfo))finishHandler;

/**
 打开指定订单的进度页面

 @param dicOrderInfo 订单信息，来自于获取用户的订单列表这个接口返回的结果
 */
- (BOOL)pushProgressPageForOrder:(NSDictionary *)dicOrderInfo inNav:(UINavigationController *)navCtl;

@end
