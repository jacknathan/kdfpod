//
//  ErrorDefine.h
//  KDFCreditcardsTool
//
//  Created by ChenYong on 2018/8/20.
//  Copyright © 2018 samoyed. All rights reserved.
//

#ifndef ErrorDefine_h
#define ErrorDefine_h

static NSString *const KDFErrorGetThirdUserID   = @"KDFErrorGetThirdUserID";    //未设置第三方用户userID
static NSString *const KDFErrorPathStr          = @"KDFErrorPathStr";           //路径错误
static NSString *const KDFErrorNoNavCtl         = @"KDFErrorNoNavCtl";          //未设置导航
static NSString *const KDFErrorNoAppKey         = @"KDFErrorNoAppKey";          //未设置AppKey
static NSString *const KDFErrorNeedLogin        = @"KDFErrorNeedLogin";         //还未登录，需要先登录
static NSString *const KDFErrorWrongParam       = @"KDFErrorWrongParam";        //参数错误
static NSString *const KDFErrorNoNetwork        = @"KDFErrorNoNetwork";         //网络不通
static NSString *const KDFErrorException        = @"KDFErrorException";         //未知的异常错误

#endif /* ErrorDefine_h */
