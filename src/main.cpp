#include <iostream>
#include <set>
#include <sstream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include <cqcppsdk/cqcppsdk.h>

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;

CQ_INIT{
	on_enable([] {
		logging::info("启用", "插件已启用");
	});
on_group_message([](const GroupMessageEvent& event) {
	string trigger = "抽签";
	if (trigger == event.message) {
		try {
			auto mem_list = get_group_member_list(event.group_id); // 获取群成员列表
			srand(time(0));
			int id = rand() % static_cast<int>(mem_list.size());//获取随机数
			string msg;
			msg += "抽到一位幸运儿" + MessageSegment::at(mem_list[id].user_id);
			send_group_message(event.group_id, msg); // 输出抽到的成员
		}
		 catch (ApiError & err) {
		  logging::warning("群聊", "私聊消息复读失败, 错误码: " + to_string(err.code));
	  }
	}
	event.block(); // 阻止当前事件传递到下一个插件
});
}