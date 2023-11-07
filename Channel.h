#pragma once 
#include"noncopyable.h"
#include<functional>
#include<memory>
#include"Timestamp.h"
class EventLoop;

//封装sockfd 感兴趣的事件 EPOLL_IN EPOLL_OUT，返回事件
class Channel:noncopyable
{
public:
    using EventCallback=std::function<void()>;
    using ReadEventCallback=std::function<void(Timestamp)>;
    Channel(EventLoop* loop,int fd);
    ~Channel();
    void handleEvent(Timestamp receiveTime);

    //设置回调接口给外部
    void setReadCallback(ReadEventCallback cb){readCallback_ =std::move(cb);}
    void setWriteCallback(EventCallback cb){writeCallback_ =std::move(cb);};
    void setCloseCallback(EventCallback cb){closeCallback_ =std::move(cb);};
    void setErrorCallback(EventCallback cb){errorCallback_ =std::move(cb);};

    void tie(const std::shared_ptr<void>&);//防止channel没有了，还在执行callback
    int fd()const{ return fd_;}
    int events() const{ return events_;}
    int set_revents(int revt)  {  revents_ = revt;}
    bool isNoneEvent()const{return events_==kNoneEvent;}
    void enableReading(){events_|=kReadEvent;update();}
        void disableReading(){events_&=~kReadEvent;update();}
        void enableWriting(){events_|=kWriteEvent;update();}
        void disableWriting(){events_&=~kWriteEvent;update();}
        void disableAll(){events_=kNoneEvent;update();}

        bool isNoneEvent()const{return events_==kNoneEvent;}
        bool isWriting()const{return events_==kWriteEvent;}
        bool isReading()const{return events_==kReadEvent;}
        int index(){return index_;}
        void set_index(int idx){index_=idx; }


        EventLoop* ownerLoop(){return loop_;}
        void remove();
        


private:
static const int kNoneEvent;
static const int kReadEvent;
static const int kWriteEvent;
EventLoop* loop_;
const int fd_;// fd  是poller监听的对象
int events_;//注册
int revents_;//返回事件
int index_;

//weak_ptr观察对象  提升成强指针，成功访问，失败不问 
std::weak_ptr<void> tie_;

bool tied_;

ReadEventCallback readCallback_;
EventCallback writeCallback_;
EventCallback errorCallback_;
EventCallback closeCallback_;
void update();
void handleEventWithGuard(Timestamp receiveTime);


};