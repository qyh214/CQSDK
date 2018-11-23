#include <CQSDK.h>
#include <string>
using namespace std;

//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger logger("PrivateMsg_EX");


//����EX���¼�Ĭ��ӵ��һ��e����,�¼���ز�������װ��e������,ͨ��ide���ٲ�ȫ

void Msg(MsgEvent*e);

//Ⱥ��
EVE_GroupMsg_EX(GroupMsg_EX) {
	logger.Debug() << DEBUGINFO << e.message;
	if (e.isAnonymous()) {
		auto info = e.getFromAnonymousInfo();
		logger.Debug() << "�����ߴ���Ϊ:" << info.���� << e.message;
	}

	//����Ⱥ��Ա
	//auto list = e.getGroupMemberList();
	//for each (auto var in list)
	//	logger.Debug() << var.tostring() << e.message;

	//ȡ�����ߵ�Ⱥ��Ϣ
	//auto player=e.getGroupMemberInfo();
	//	logger.Debug() << player.tostring() << e.message;

	//����Ⱥ����
	//e.setGroupAnonymous(true);

	//���������Ϊ����Ա
	//e.setGroupAdmin(true);

	//���ý���,Ĭ��1����
	//e.setGroupBan();

	//e.setGroupSpecialTitle("Ⱥͷ��");
	//e.setGroupCard("Ⱥ��Ƭ");
	//e.setGroupKick();//�ɵ������

	Msg(&e);
}
//˽����Ϣ
EVE_PrivateMsg_EX(PrivateMsg_EX) {
	logger.Debug() << DEBUGINFO << e.message;
	Msg(&e);
}
//������
EVE_DiscussMsg_EX(DiscussMsg_EX) {
	logger.Debug() << DEBUGINFO << e.message;
	Msg(&e);
}



void Msg(MsgEvent*e) 
{

	// ���һ�����¼��йص���Ϣ����
	// �����Ϣ�����Ѿ��Զ������¼���Ӧ��Ⱥ���ߺ���
	auto msg = e->sendMsg();
	// ���������ض����˷�����Ϣ,�������123456
	// ������ֱ�ӵ���API
	//sendPrivateMsg(123456, "���");
	// ����ʹ��MsgSend
	//MsgSend P123456(123456, msgtype::����);
	//P123456 << "���" << send;

	auto message = e->message;

	// ��ͨ�ķ���һ����Ϣ
	if (!message.compare("CQ:msg1"))
		e->sendMsg("�յ���Ϣ��!");

	// ʹ��<<��������Ϣ
	if (!message.compare("CQ:msg2"))
		//һ��Ҫĩβ����<<send�Żᷢ�ͳ�ȥ
		msg << "�յ���Ϣ��!" << send;

	// ǿ�����Ϣ���ͷ�ʽ
	if (!message.compare("CQ:msg3"))
		// ���������ɶ���������
		msg
		<< "������Ϊ:" << e->fromQQ
		<< ",��ϢΪ:" << e->message
		<< send;

	if (!message.compare("CQ:image")) {
		logger.Debug() << "rawģʽ:" << msg.isRAW() << send;
		// ����һ��ͼƬ
		msg << code::image("123.gif") << send;
	}

	if (!message.compare("CQ:face"))
		//����һ������
		msg << code::face(face::����) << send;

	if (!message.compare("CQ:raw"))
		msg
		// RAW ��ʾ�������Ϣ����ԭ������
		// �����ǽ�����CQ��,���������й���,���緢��ͼƬ
		<< RAW << code::at(e->fromQQ)
		// CODE ��ʾ�������Ϣ��������ΪCQ��
		// Ĭ�Ͻ���
		<< CODE << code::face(face::����)
		<< send;

	if (!message.compare("CQ:effect"))
		// ����һ��ħ������,��CQ����뵥��һ����Ϣ
		e->sendMsg(code::effect("art", 2003, "ħ����Ϣ"));
}