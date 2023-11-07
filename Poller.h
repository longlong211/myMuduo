#include<vector>
#include<unordered_map>
#include"Timestamp.h"
#include"noncopyable.h"
class Channel;
class EventLoop;
class Poller:noncopyable
{
private:
    /* data */
    EventLoop *ownerLoop;
public:
    using ChannelList=std::vector<Channel*>;
    Poller(EventLoop *loop);
    virtual ~Poller();
    virtual Timestamp poll(int timeoutMs,ChannelList *activeChannel)=0;//启动epoll_wait
    virtual void updateChannel(Channel* channel)=0;
    virtual void removeChannel(Channel* channel)=0;
    bool hasChannel(Channel* channel)const;
    static Poller* newDefaultPoller(EventLoop *loop);//获取实例；

protected:
    using ChannelMap=std::unordered_map<int,Channel*>;
    ChannelMap Channels_;
};

