//
// Created by HAN on 2022/3/9.
//

#ifndef EMAIL_USER_H
#define EMAIL_USER_H
#include <winsock2.h>
#include "Email.h"
#include "POP3Connector.h"
#include "STMPConnector.h"
#include "util.h"
#include <stdlib.h>
#include <map>
#pragma comment(lib,"ws2_32.lib")
class User {
private:

    //POP3Connector * pop3{};
    //SMTPConnector * smtp{};

public:
    string email;
    string password;
    vector<Email> emailist ;///弃用！不用vector的原因时每当有新邮件产生的时候会让整体的顺序+1 从而错乱

                    // closetodo: 更改这个vector 创建一个uidi-email的对应
    //// 通过UIDL识别码来获取到指定email
    map<string,Email> uidlEmial;


                    //closetodo: 在此处创建一个hashmap string - int   string保存右键的uidl。然后利用该表来保存序号
  /// 该列表存储实时的存在邮件序号与对应的UIDL唯一识别码
    vector<string> allUIDLs;



    User();
    /**
     *初始化用户的一般形式，但该函数不能确保用户名与密码正确
     * @param email
     * @param password
     */
    User(string email,string password);

    /**
     * 该函数在用户第一次注册的时候使用 会在当前目录下生成 ”邮箱。conf“ 文件来保存信息
     * 重新启动时可通过调用 ‘getallUserfromConf’ 函数来获取全部已经注册的用户
     *
     * @param emails
     * @param passwords
     * @param init  无所谓是true还是false  只是与上一个构造函数区别
     */
    User(string emails, string passwords,bool init);
    ~User();

    /**
     *
     * 获取全部已经注册过的用户
     * @return
     */
    static vector<User>  getallUserfromConf();


    /**
     * 刷新函数  //todo : 待完成
     *
     */
    bool refreshemail();


    /**
     * 通过vector<string> allUIDLs 对应的序号 （id）  来完成邮件的接受
     * @param id
     *
     * 函数完成后会在对应用户的文件夹（以邮箱命名）  下生成以UIDL明明的文件
     */
    void RetrEmail(int id);


    /**
     *
     * 初始化邮箱信息 （Top命令）
     * 该函数巨尼玛慢！！！  希望通过异步的方式解决
     *
     *  可以维护 map<string,Email> uidlEmial; 即通过uisl即可获取到用户邮箱的简介信息
     *  同时维护    vector<string> allUIDLs;
     */
    void  getallEmailinfo();



/**
 *
 * @param subject  邮件主题
 * @param emialName  发送的目标邮件地址
 * @param contextpath  发送的内容文件
 * @param attachname   发送的附件       ** 可选参数
 * @param isutf8   是否采用utf-8 的格式  ** 可选参数  如果不选就是那个gb18030 的格式
 */
    //
    // a2.SendEmail("hello","992115865@qq.com","test.txt","email.cbp",true);
    void SendEmail(string subject,const string& emialName,string contextpath,string attachname="",bool isutf8 = false);


    void DeleteEmail(int id);
};

#endif //EMAIL_USER_H
