#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>

//extern QSqlDatabase db;
extern quint32 current_userID;

class DataDB
{
public:
    explicit DataDB();
    ~DataDB();
    //初始化连接
    //void createConnection();
    //注册
    bool registerUser(const quint32 user_id, const QString& password);
    //登录功能
    bool loginUser(const quint32 user_id, const QString& password);
//    UserInfo selectUserInfoById(const quint32 id);//存在返回true，不存在返回false
//    //查询当前全部用户的数据库操作--静态sql
//    QList<QByteArray> selectAllFriendsUserInfo(quint32 UserId);
//    //注册
//    void registerUserInfo(const UserInfo& user);//一个用户结构
    //添加好友
    void addFriendship(quint32 friend_id);
    //删除好友
    void deleteFriendship(quint32 friend_id);
//    //判断好友关系是否存在
//    bool friendshipExist(quint32 Id1,quint32 Id2);
    //添加聊天信息
    void addMsg(quint32 msg_id, quint32 sender_id,quint32 receiver_id,QString Msg,QString Time);
//    //获取最大的Id值
//    quint32 selectMaxId();
    //单例设计模式--应对数据库的对象的内存使用
    static DataDB* GetInstance();

//    //群组操作
//    //添加群聊关系
//    void addGroupship(quint32 UserID,quint32 GroupID,quint32 UserPermission = 0);
//    void registerGroupInfo(const GroupInfo& Group);
//    quint32 selectMaxGroupId();
//    GroupInfo selectGroupInfoByID(quint32);
//    // Id1用户ID,Id2群聊ID,返回Id1是否在Id2中
//    bool groupshipExist(quint32 Id1, quint32 Id2);
//    QList<QByteArray> selectAllGroupInfo(quint32 ID);
//    QList<quint32> selectAllGroupMember(quint32 ID);

//    //修改用户名和头像
//    void updUsername(quint32 ID,QString Username);
//    void updAvatar(quint32 ID,QString Avatar);
private:
    QSqlDatabase sqldb;
    static DataDB* db;
};

#endif // DATABASE_H
