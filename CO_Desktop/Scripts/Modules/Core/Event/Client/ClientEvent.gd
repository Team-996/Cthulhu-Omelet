extends Node

signal request_client_startup_event         #请求大世界客户端事件，如果大世界客户端没有该进程则启动大世界客户端
signal request_client_shutdown_event        #请求大世界客户端关闭事件
signal client_startup_event                 #当大世界客户端成功启动时的事件
signal client_shutdown_event                #当大世界客户端被关闭时的事件，该事件不能保证关闭一瞬间触发
