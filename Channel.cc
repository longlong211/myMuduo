#include"Channel.h"
#include"EventLoop.h"
#include<sys/epoll.h>
#include"Logger.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

    Channel::Channel(EventLoop* loop,int fd)
    :loop_(loop)
    ,fd_(fd)
    ,events_(0)
    ,revents_(0)
    ,index_(-1)
    ,tied_(false)
    {
        LOG_INFO("channel handelevnet revents%d\n",revents_);

    }
    Channel::~Channel(){
        //if(loop->isInLoopEvent)
    }
     void Channel::tie(const std::shared_ptr<void>& obj)
     {
            tie_=obj;
            tied_=true;
     }
     void Channel::update()//负责在poller里面改fd的事件，epoll_ctl
     {
        //通过channel所属的eventloop 调用poller方法，注册fd的events事件
       // loop_->updateChannel(this);

     }
     void Channel::remove()
     {
        // loop_->removeChannel(this);
     }
     void Channel::handleEventWithGuard(Timestamp receiveTime)
     {
        if((revents_ & EPOLLHUP)&& !(revents_&EPOLLIN))
        {
            if(closeCallback_){
                closeCallback_();
            }
        }
        if(revents_&EPOLLERR)
        {
            if(errorCallback_){
                errorCallback_();
            }
        }
        if(revents_&(EPOLLIN|EPOLLPRI))
        {
            if(readCallback_){
                readCallback_(receiveTime);
            }
        }
     }

    void Channel::handleEvent(Timestamp receiveTime)
    {
        
        if (tied_)
        {
            std::shared_ptr<void> guard;
            guard = tie_.lock();
            if (guard)
            {
            handleEventWithGuard(receiveTime);
            }
        }
        else
        {
            handleEventWithGuard(receiveTime);
        }

    }