#pragma once

enum EErrCode
{
    ERR_OK = 0,		//�ɹ�		
    ERR_SYSTEM,		//ϵͳ����
    ERR_UNKNOW,		//δ֪����
    ERR_ALREADYONLINE,	//�˺�������
    ERR_INLOADUSERDATA, //�˺���Ϣ������
    ERR_DATABASEERR,    //���ݿ����ʧ��
    ERR_NOUSERDATA,     //���˺�����
    ERR_NOROLEDATA,     //�޽�ɫ����
    ERR_ROLEDELLIMIT,   //ÿ��ֻ��ɾ��һ����ɫ
    ERR_CREATEMAXROLE,  //�ﵽ������ɫ�����
    ERR_USESTATEWRONG,  //��ɫ״̬����
    ERR_ROLENAMEEXIST,  //��ɫ���Ѵ���
    ERR_LOGINTIMEOUT,   //�˺ŵ�½��ʱ
    ERR_ROLEINCREATE,   //��ɫ������
    ERR_ROLEGENDER,     //�Ƿ��Ľ�ɫ�Ա�
    ERR_ROLEJOB,        //�Ƿ��Ľ�ɫְҵ
    ERR_GETROLEDATA,    //��ȡ��ɫ����ʧ��
    ERR_NOROLEINLIST,   //��ɫ�б����޴˽�ɫ
    ERR_ROLEDESTROY,    //��ɫ��ɾ��
    ERR_ALREADYINGAME,  //��ɫ�Ѿ�����Ϸ��
    ERR_GSNOTEXIST,     //Game Server������
    ERR_SELECTTIMEOUT,  //ѡ��ɫ��ʱ
    ERR_CREATETIMEOUT,  //������ɫ��ʱ
    ERR_ENTERGSTIMEOUT, //����Game Server��ʱ
    ERR_ROLEACTIONFAIL, //��ɫִ�д���
    ERR_UNKNOWEXITTYPE, //δ֪����������
    ERR_NOMAPDATA,      //�Ҳ�����ͼ��Ϣ
    ERR_MOVEFAIL,       //�ƶ�ʧ��
    ERR_MOVETOOFAST,    //�ƶ��ٶ�̫��
    ERR_MOVESTIFF,      //�ƶ�ʱ����Ӳֱ״̬
    ERR_TURNFAIL,       //ת��ʧ��
    ERR_TURNSTIFF,      //ת��ʱ����Ӳֱ״̬
    ERR_NOMOVABLEPOINT, //û�п��ƶ���
    ERR_REPEATLOGIN,    //ͬһ�ʺ��ظ���½
    ERR_NOGRID,         //û���߼�����Ϣ
    ERR_NOMONSTER,      //û�й�����Ϣ
    ERR_TARGETTOOFAR,   //Ŀ�����̫Զ
    ERR_NOGMCMD,        //GMָ�����
    ERR_EXEGMCMDFAIL,   //GMָ��ִ��ʧ��
    ERR_GMCMDNORIGHT,   //��Ȩ��ִ��GMָ��
    ERR_RULECHECKFAIL,  //��ͼ������ʧ��
    ERR_BANWORD,        //�벻Ҫʹ�����д�
    ERR_ILLEGALITY,     //�����Ƿ��ַ�
    ERR_BAG_MAPPINGS,   //����ӳ���쳣
    ERR_VERIFY_FAIL_AGAIN,    //��֤����������������
    ERR_VERIFY_FAIL_CANCEL,   //��֤����������
    ERR_LOGIN_WRONG_USER,         // �޴��û�
    ERR_LOGIN_WRONG_PASSWORD,     // ������������
    ERR_NOUSCMD,        //�û�ָ�����
    ERR_NOUSSCRIPT,     //�û�ָ��ű�������
    ERR_EXECUSCMDFAIL,  //�û�ָ��ִ��ʧ��
    ERR_MOVE_PUNISH_CONTINUOUS,     /// �ƶ������쳣�ͷ�
    ERR_MOVE_PUNISH_SAMPLING,       /// �ƶ������쳣�ͷ�
    ERR_MS_PUNISH_SAMPLING,         /// MS�����쳣�ͷ�
    ERR_GS_KICK_PLAYER,             /// GS���˾���ԭ����Э��������
    ERR_GP_PUNISH,                  /// ����ҳͷ�
    ERR_SVR_STOP,                   /// ������ֹͣ
    ERR_NAME_LENGTH,                /// ����̫��
    ERR_CREATE_ROLE_IN_COMBAT,      /// �����ڶ�ս��������ɫ
    ERR_GS_OVERLOAD,                /// GS�����Ѵ�����
    ERR_GS_MIGRATE_DATA,            /// GSǨ���������
    ERR_USERDATA_ABNORMAL,          /// �˺������쳣
    ERR_CREATE_ROLE_IN_CFG,         /// ��ʱ�رմ�����ɫ����
    ERR_BAG_SPACE_NOT_ENOUGH,       /// �����ռ䲻��
    ERR_NO_CFG,                     /// δ�ҵ�����
    ERR_INVALID_CFG,                /// ������Ч
    ERR_CREATE_ROLE_CODE_NOTMATTCH, /// ������ɫ�����벻����
    //////////////////////////////////////////////////////////////////////////
    ERR_ITEM_NOT_ENOUGH = 1000,     /// ��Ʒ����
    ERR_ITEM_SPACE_FULL,            /// ��������
    ERR_ITEM_ADD,                   /// ��Ʒ���ʧ��
    ERR_ITEM_DESTROY,               /// ��Ʒɾ��ʧ��
    ERR_ITEM_MOVE,                  /// ��Ʒ�ƶ�ʧ��
    ERR_ITEM_SPLIT,                 /// ��Ʒ���ʧ��
    ERR_ITEM_BIND,                  /// ��Ʒ��ʧ��
    ERR_ITEM_APPLY,                 /// ��Ʒʹ��ʧ��
    ERR_ITEM_SCRIPT_NOT_EXIST,      /// ��Ʒ�ű�������
    ERR_ITEM_CANT_EQUIP,            /// ����Ʒ����װ��
    ERR_ITEM_NOT_EQUIP_SITE,        /// Ŀ��λ�ò���װ��λ
    ERR_ITEM_EQUIP_NOT_SUIT_SITE,   /// װ����ƥ��װ��λ
    ERR_ITEM_EQUIP_JOB,             /// ְҵ��ƥ��
    ERR_ITEM_EQUIP_GENDER,          /// �Ա�ƥ��
    ERR_ITEM_EQUIP_LEVEL,           /// δ�ﵽװ���ȼ�
    ERR_ITEM_EQUIP_BIND_TYPE,       /// װ�������Ͳ�ƥ��
    ERR_ITEM_EQUIP_WEIGHT,          /// װ�����ز���
    ERR_ITEM_MAX_BRAWN,             /// ��������
    ERR_ITEM_MAX_PHY_ATK,           /// ����������
    ERR_ITEM_MAX_MAG_ATK,           /// ħ����������
    ERR_ITEM_MAX_TAO_ATK,           /// ������������
    ERR_ITEM_ARRANGE,               /// ��Ʒ����ʧ��
    ERR_ITEM_PICKUP,                /// ��Ʒʰȡʧ��
    ERR_ITEM_PICKUP_OWNER,          /// ����ƷĿǰ��������
    ERR_ITEM_PICKUP_TEAM,           /// �㲻�ڿ�ʰȡ�˵Ķ�����
    ERR_ITEM_DROP,                  /// ��Ʒ����ʧ��
    ERR_ITEM_DROP_NOT_BAG_SITE,     /// ��Ʒ���ڱ������ɶ���
    ERR_ITEM_DROP_MAP,              /// ��ǰ��ͼ���ɶ�����Ʒ
    ERR_ITEM_DROP_ITEM,             /// ����Ʒ���ɶ���
    ERR_ITEM_TIE_UP,                /// ��Ʒ����ʧ��
    ERR_ITEM_ENHANCE_OK,            /// ǿ�����
    ERR_ITEM_ENHANCE_MUST_WEAPON,   /// ֻ����������ǿ��
    ERR_ITEM_ENHANCE_DISABLE,       /// ����������ǿ��
    ERR_ITEM_ENHANCE_UPGRADING,     /// ǿ����Ʒ�Ѿ�����������
    ERR_ITEM_ENHANCE_MAX_LEVEL,     /// �Ѿ�ǿ������ߵȼ�
    ERR_ITEM_ENHANCE_ITEM,          /// ǿ����Ʒ���β���ȷ
    ERR_ITEM_ENHANCE_MATERIAL,      /// ǿ����Ʒ���ϲ���ȷ
    ERR_ITEM_DRILL_OK,              /// ������
    ERR_ITEM_DRILL_MUST_EQUIP,      /// ֻ��װ�����ܴ��
    ERR_ITEM_DRILL_DISABLE,         /// ��װ�����ɴ��
    ERR_ITEM_DRILL_MATERIAL,        /// ��Ҫ��ײ���
    ERR_ITEM_DRILL_FULL,            /// װ���������Ѵﵽ����
    ERR_ITEM_DRILL_RATE,            /// ���ʧ��
    ERR_ITEM_SYNTHESIS_OK,          /// װ���ϳɳɹ�
    ERR_ITEM_SYNTHESIS_MATERIAL,    /// �ϳɲ��ϲ���ȷ
    ERR_ITEM_SYNTHESIS_GEM_ENOUGH,  /// �ϳɱ�ʯ����
    ERR_ITEM_SYNTHESIS_GEM_ID,      /// ��ʯ���Ͳ���ͬ
    ERR_ITEM_SYNTHESIS_CANT,        /// ��Ʒ���ɺϳ�
    ERR_ITEM_SYNTHESIS_LEVEL,       /// �ϳɷ�����ȷ
    ERR_ITEM_SYNTHESIS_RATE,        /// �ϳ�ʧ��
    ERR_ITEM_EMBED_OK,              /// ��ʯ��Ƕ�ɹ�
    ERR_ITEM_EMBED_DISABLE,         /// ��ʯ������Ƕ
    ERR_ITEM_EMBED_FULL,            /// ��Ʒ��Ƕ����
    ERR_ITEM_EMBED_MATERIAL,        /// ��Ƕ���ϲ���ȷ
    ERR_ITEM_EMBED_MISMATCH,        /// ��ʯ��ƥ��
    ERR_ITEM_EMBED_RATE,            /// ��Ƕʧ��
    ERR_ITEM_DIG_OK,                /// ��ʯժ���ɹ�
    ERR_ITEM_DIG_SLOT,              /// ��ʯ��λ����ȷ
    ERR_ITEM_DIG_MATERIAL,          /// ժ�����ϲ���ȷ
    ERR_ITEM_DIG_MATERIAL_LEVEL,    /// ��ʯժ�����ȼ�����
    ERR_ITEM_IDENTIFY_OK,           /// װ������
    ERR_ITEM_IDENTIFY_DISABLE,      /// ��װ�����ɼ���
    ERR_ITEM_REFINE_OK,             /// װ�������ɹ�
    ERR_ITEM_REFINE_DISABLE,        /// ��װ�����ɾ���
    ERR_ITEM_REFINE_TOP_LEVEL,      /// ��װ���Ѿ���������
    ERR_ITEM_REFINE_LEVEL,          /// �����ȼ�����ȷ
    ERR_ITEM_REFINE_MATERIAL,       /// �������ϲ���ȷ
    ERR_ITEM_REFINE_NOT_ENOUGH,     /// �������ϲ���
    ERR_ITEM_REFINE_RATE,           /// ����ʧ��
    ERR_ITEM_REPAIR_OK,             /// װ������ɹ�
    ERR_ITEM_REPAIR_DISABLE,        /// ��װ����������
    ERR_ITEM_REPAIR_INFINITE,       /// ��װ���;�����
    ERR_ITEM_REPAIR_MAX_DURABILITY, /// ��װ���־�����
    ERR_ITEM_NOT_EXIST,             /// ����Ʒ������
    ERR_ITEM_DUP_SITE,              /// �����غ���Ʒ
    ERR_ITEM_USEZEROAUTODEL,        /// ʹ�ô���Ϊ���Զ�ɾ��
    ERR_ITEM_DURZEROAUTODEL,        /// �־�Ϊ��Ϊ���Զ�ɾ��
    ERR_ITEM_TIMEUPAUTODEL,         /// ��Ʒʹ��ʱ�䵽�Զ�ɾ��
    ERR_ITEM_BAG_WEIGHT,            /// �㱳������ô�ණ��
    ERR_ITEM_GUID_MAPPING,          /// ������ƷGUIDӳ�䲻һ��
    ERR_ITEM_NO_DATA_ROW,           /// ��Ʒģ�岻����
    ERR_ITEM_SITE,                  /// ��Ʒλ�÷����쳣
    ERR_ITEM_AMOUNT,                /// ��Ʒ���������쳣
    ERR_ITEM_EXPIRED,               /// ��Ʒ�Ѿ�����
    ERR_ITEM_CREATE_BAG,            /// ��������ʧ��
    ERR_ITEM_SWAP,                  /// ������Ʒʧ��
    ERR_ITEM_ADD_BIND_TYPE,         /// �����Ʒ������ʹ���
    ERR_ITEM_DROP_IN_SAFE,          /// ��ȫ�����ɶ�����Ʒ
    ERR_ITEM_BAG_OPT,               /// ����������
    ERR_ITEM_FORBID_HERO_BAG,       /// ��Ʒ��ֹ����Ӣ�۰���
    ERR_ITEM_FORBID_WAREHOUS,       /// ��Ʒ��ֹ����ֿ�
    ERR_ITEM_PICK_UP_DROPED,        /// ����ʰȡ�Ѿ���������Ʒ
    ERR_ITEM_RANGE_PICK_UP_NON,     /// ��Χʰȡ ��Ʒ��ʰȡ
    ERR_ITEM_PICK_UP_NON,           /// ����ʰȡ ��ƷΪ��
    ERR_ITEM_PICK_UP_NO_SHOW,       /// ����ʾ�Ĵ�����
    //////////////////////////////////////////////////////////////////////////
    ERR_SKILL_NOT_EXIST = 1100,     /// ���ܲ�����
    ERR_SKILL_NOT_LEARNED,          /// ���ܻ�ûѧϰ
    ERR_SKILL_NO_TARGET,            /// Ŀ�겻����
    ERR_SKILL_SWITCH,               /// ���ܿ���ʧ��
    ERR_SKILL_CD_CHAIN,             /// ���ܻ�����ȴ
    ERR_SKILL_COST_ATTR,            /// �������Կ�������
    ERR_SKILL_COST_ITEM,            /// ������Ʒ��������
    ERR_SKILL_NEED_WEAPON,          /// ������Ҫ����
    ERR_SKILL_JUJU,                 /// ��Ҫ��ȷ�ķ���
    ERR_SKILL_CAST_DISTANCE,        /// ����ʩ�ž��벻��
    ERR_SKILL_MISS,                 /// ����MISS
    ERR_SKILL_ROLE_DEAD,            /// �������
    ERR_SKILL_CANT_PHY_ATK,         /// ����ʹ��������
    ERR_SKILL_CANT_MAG_ATK,         /// ����ʹ��ħ������
    ERR_SKILL_COLLIDE,              /// ���ڳ�ײ״̬����ʹ�ü���
    ERR_SKILL_REPELLED,             /// ���ڻ���״̬����ʹ�ü���
    ERR_SKILL_FIRE_ACTIVE,          /// �һ���Ч
    ERR_SKILL_FIRE_EXPIRE,          /// �����ѹ���
    ERR_SKILL_CANT_USE,             /// ���ܲ���ʹ��
    ERR_SKILL_DIG_MEAT,             /// û���ڵ��κ���Ʒ
    ERR_SKILL_POWER_HIT_ACTIVE,     /// ��ɱ����
    ERR_SKILL_POWER_HIT_DONE,       /// ��ɱ����
    ERR_SKILL_ATTACK_TIME,          /// �չ�ʱ��δ��
    ERR_SKILL_FIRE_EMPTY,           /// �һ����
    ERR_SKILL_POWER_DISABLE,        /// ��ɱʱ��δ��
    ERR_SKILL_POWER_EMPTY,          /// ��ɱ����
    ERR_SKILL_CISHA_EMPTY,          /// ��ɱ����
    ERR_SKILL_BANYUE_EMPTY,         /// ���»���
    ERR_SKILL_NORMAL_EMPTY,         /// �չ�����
    ERR_SKILL_REPEL_COLLIDE,        /// ��ײ���
    ERR_SKILL_SCRIPT_NOT_EXIST,     /// ���ܽű�������
    ERR_SKILL_UNVALID,              /// ���ܱ���ֹ
    ERR_SKILL_ALREADY_EXIST,        /// �����Ѵ���
    ERR_SKILL_JOB_MISMATCH,         /// ְҵ��ƥ��
    ERR_SKILL_EXIST_SAME_CHAIN,     /// ͬһ�������ļ����Ѵ���
    ERR_SKILL_REACH_UPLIMIT,        /// �Ѵ�����

    //////////////////////////////////////////////////////////////////////////
    ERR_BUFF_NOT_EXIST = 1200,      /// BUFF������
    ERR_BUFF_CANT_CANCEL,           /// BUFF����ȡ��
    //////////////////////////////////////////////////////////////////////////
    ERR_TEAM_ALREADY_EXIST = 1300,  /// �����Ѵ��ڣ����鴴��ʧ��
    ERR_TEAM_MAP,                   /// �õ�ͼ�������
    ERR_TEAM_TARGET_MAP,            /// �Է����ڵ�ͼ�������
    ERR_TEAM_SWITCH_REFUSE,         /// �Է������˾ܾ����
    ERR_TEAM_NO_PLAYER,             /// ��Ҳ����ڻ�������
    ERR_TEAM_TARGET_HAS_TEAM,       /// �Է��Ѿ��ж���
    ERR_TEAM_TARGET_NO_TEAM,        /// �Է�û�ж���
    ERR_TEAM_NO_RIGHT,              /// û��Ȩ��
    ERR_TEAM_FULL,                  /// ��������
    ERR_TEAM_INVITER_OFFLINE,       /// �������Ѿ����� 
    ERR_TEAM_INVITE_EXPIRE,         /// �����ѹ���
    ERR_TEAM_REFUSE,                /// �Է��ܾ����
    ERR_TEAM_TARGET_LEADER_OFFLINE, /// �Է��ӳ�������
    ERR_TEAM_JOIN_REFUSE,           /// �Է��ӳ���ͬ����������
    ERR_TEAM_INVITE_TIME,           /// �������Ƶ��
    ERR_TEAM_JOIN_TIME,             /// �������Ƶ��
    ERR_TEAM_AUTH_TIME,             /// Ȩ�ޱ������Ƶ��
    ERR_TEAM_QUERY_TIME,            /// �����ѯ����Ƶ��
    ERR_TEAM_JOIN_EXPIRE,           /// �����ѹ���
    //////////////////////////////////////////////////////////////////////////
    ERR_QUICK_BAR_ITEM_NOT_EXIST = 1400,    /// ��Ʒ������
    ERR_QUICK_BAR_SKILL_NOT_EXIST,          /// ���ܲ�����
    //////////////////////////////////////////////////////////////////////////
    ERR_DEPOSIT_SAVE_OK = 1500,             /// ���ҳɹ�
    ERR_DEPOSIT_TALK_OK,                    /// ȡ��ҳɹ�
    ERR_DEPOSIT_DROP_OK,                    /// ����ҳɹ�
    ERR_DEPOSIT_NOT_ENOUGH_GOLD,            /// ��Ҳ���
    ERR_DEPOSIT_NOT_ENOUGH_BIND_GOLD,       /// �󶨽�Ҳ���
    //////////////////////////////////////////////////////////////////////////
    ERR_TRADE_P2P_OK = 1600,                /// ���׳ɹ�
    ERR_TRADE_P2P_TRADING,                  /// �Է�������
    ERR_TRADE_P2P_INVITE_EXPIRE,            /// ���������ѹ���
    ERR_TRADE_P2P_REFUSE,                   /// �Է��ܾ�����
    ERR_TRADE_P2P_NOT_ENOUGH_GOLD,          /// û���㹻�Ľ��
    ERR_TRADE_P2P_GOLD_FULL,                /// ������
    ERR_TRADE_P2P_DATA,                     /// ���������ѱ��
    ERR_TRADE_P2P_ITEM_BIND,                /// ����Ʒ���ɽ���
    ERR_TRADE_P2P_ITEM_TRADABLE,            /// ����Ʒ���ɽ���
    ERR_TRADE_P2P_ITEM_SITE,                /// ��Ʒ�����ڱ�����
    ERR_TRADE_P2P_DUP_ITEM,                 /// �����������ϼ�
    ERR_TRADE_P2P_FAILED,                   /// ����ʧ��
    ERR_TRADE_P2P_GOLD_LOCK,                /// ���δ����
    ERR_TRADE_P2P_LEVEL,                    /// ����˫���ȼ�����

    ERR_TRADE_STALL_OK = 1620,              /// ��̯�ɹ�
    ERR_TRADE_STALL_LEVEL,                  /// ��̯�ȼ�����
    ERR_TRADE_STALL_PK_RED,                 /// �������ɰ�̯
    ERR_TRADE_STALL_PK_BLACK,               /// �������ɰ�̯
    ERR_TRADE_STALL_GOLD_COST,              /// ��̯��Ҳ���
    ERR_TRADE_STALL_GRID,                   /// ��λ�ò��ɰ�̯
    ERR_TRADE_STALL_REFUSE,                 /// �����Ѿ����˰�̯
    ERR_TRADE_STALL_NOT_READY,              /// ��̯δ׼��
    ERR_TRADE_STALL_ITEM,                   /// ��̯��Ʒ����
    ERR_TRADE_STALL_PRICE_LESS_ZERO,        /// ��̯��Ʒ���۲���С����
    ERR_TRADE_STALL_PRICE_TYPE,             /// ��̯��Ʒ�۸����Ͳ���
    ERR_TRADE_STALL_ITEM_AMOUNT,            /// ��Ʒ����Ϊ�㲻���ϼ�
    ERR_TRADE_STALL_ITEM_BIND,              /// �Ѱ���Ʒ���ɰ�̯����
    ERR_TRADE_STALL_ITEM_TRADABLE,          /// ����Ʒ���ɽ���
    ERR_TRADE_STALL_ITEM_SITE,              /// ��̯ʱ��Ʒ�����ڱ�����
    ERR_TRADE_STALL_ARRANGE,                /// ���ڰ�̯״̬�������¼�
    ERR_TRADE_STALL_TARGET_NOT_START,       /// �Է���δ��ʼ��̯
    ERR_TRADE_STALL_ITEM_DATA,              /// ��Ʒ�����ѱ��
    ERR_TRADE_STALL_ITEM_NOT_ENOUGH,        /// ��Ʒ��������
    ERR_TRADE_STALL_ITEM_NOT_SELL,          /// ��Ʒû���ϼ�
    ERR_TRADE_STALL_READY_CD,               /// ��̯׼����ȴʱ��δ��
    ERR_TRADE_STALL_ITEM_NOT_BUY,           /// ̯λ���չ�����Ʒ
    ERR_TRADE_STALL_ITEM_MAX_BUY_AMOUNT,    /// �ﵽ�չ���������
    ERR_TRADE_STALL_OWNER_BAG_FULL,         /// ̯����������

    //////////////////////////////////////////////////////////////////////////
    ERR_ROLE_OK = 1650,                     /// �ɹ�
    ERR_ROLE_NOT_ENOUGH_POINT,              /// ���Ե㲻��
    ERR_ROLE_QUERY_NULL,                    /// Ŀ�겻���ڻ�����
    ERR_ROLE_LC_DOWN,                       /// �������������
    ERR_ROLE_DROP_GRID,                     /// ����û�п��е�λ�ÿ��Զ���
    ERR_ROLE_SITE,                          /// ��Ч�ı���λ��
    ERR_ROLE_REQUEST_SEG_TO_FAST,           /// ��Ʒ�������
    ERR_ROLE_PK,                            /// PKֵ����
    ERR_ROLE_ARRANGE_BAG_TOO_FAST,          /// ��Ʒ�������Ƶ��
    ERR_ROLE_PK_PROTECTED,                  /// �����������򱣻�
    ERR_ROLE_QUEST_QUERY_TOO_FAST,          /// �����ѯ����Ƶ��
    ERR_ROLE_MOVE_ITEM_TOO_FAST,            /// ��Ʒ�ƶ�����Ƶ��
    ERR_ROLE_RIDE_TOO_FAST,                 /// �����������Ƶ��
    ERR_ROLE_RIDE_NULL,                     /// ����װ������
    ERR_ROLE_RIDE_DIE,                      /// ��������
    ERR_ROLE_RIDE_NOT_USE,                  /// ���״̬�²���ʹ��
    ERR_ROLE_FASHION_TOO_FAST,              /// ʱװ��������Ƶ��
    ERR_ROLE_FASHION_NULL,                  /// ����װ��ʱװ
    ERR_ROLE_FASHION_DIE,                   /// ʱװ�;ò���
    ERR_ROLE_FASHION_WEAPON_TOO_FAST,       /// ʱװ������������Ƶ��
    ERR_ROLE_FASHION_WEAPON_NULL,           /// ����װ��ʱװ����
    ERR_ROLE_FASHION_WEAPON_DIE,            /// ʱװ�����;ò���

    //////////////////////////////////////////////////////////////////////////
    ERR_NODGNDATA = 1700,                   /// ���������Ҳ���
    ERR_NODGNMAP,                           /// ������ͼ������
    ERR_CHECKDGNMAP,                        /// ������ͼ���ʧ��

	ERR_VIP_ENABLE = 1800,					///VIP�Ѿ�����
	ERR_VIP_INVALID,						///VIP�ȼ���Ч
	ERR_VIP_INGOT,							///Ԫ������
	ERR_VIP_ITEM_ENABLE,					///VIP�����Ѽ���
	ERR_VIP_ITEM_BUY,						///VIP�����ѹ���
	ERR_VIP_ITEM_INVALID,					///VIP������Ч
	ERR_VIP_ITEM_NOTSELL,					///VIP�������¼�
    ERR_VIP_ITEM_DISABLE,                   ///VIP���߲��ܵ���
	ERR_VIP_APPLY,							///VIP����δ����
	ERR_VIP_SCRIPT,							///VIP���߽ű�������

    ERR_DUMMY_NO_ACCESS = 1900,             ///û�п���Ӣ�۵�Ȩ��
    ERR_DUMMY_TOO_FAR,                      ///����Ӣ��̫Զ
    ERR_DUMMY_NOT_ATTACK,                   ///Ӣ�۲��ڹ���״̬
    ERR_DUMMY_NOT_JOINT_SKILL,              ///���Ǻϻ�����
    ERR_DUMMY_HAS_JOINT,                    ///�Ѿ�׼���ϻ���
    ERR_DUMMY_NOT_ENOUGH_XP,                ///ŭ��δ��
    ERR_HERO_LORD_OFFLINE,                  ///���˲�����
    ERR_MAP_CANT_GEN_HERO,                  ///��ͼ��ֹ�ٻ�Ӣ��

    //////////////////////////////////////////////////////////////////////////
    ERR_ETASK_FULL = 2300,                  /// ��������
    ERR_QUEST_IN_FINISHED,                  /// �����Ѿ���ɹ���
    ERR_QUEST_IN_CURRENT,                   /// �����Ѿ��ӹ���
    ERR_QUEST_REQ_WEEK_COUNT,               /// ���ܿɽӴ�������
    ERR_QUEST_REQ_DAY_COUNT,                /// ���տɽӴ�������
    ERR_QUEST_REQ_TIME,                     /// ��������ʱ�䲻��
    ERR_QUEST_REQ_LEVEL,                    /// ��������ȼ�����
    ERR_QUEST_REQ_ATT,                      /// �����������Բ���
    ERR_QUEST_REQ_PROLOGUE,                 /// ��������ǰ�ò���
    ERR_QUEST_REQ_ITEM,                     /// ����������Ʒ����
    ERR_QUEST_REQ_JOB,                      /// ��������ְҵ����
    ERR_QUEST_REQ_GENDER,                   /// ���������Ա𲻷�
    ERR_QUEST_NOT_IN_CURRENT,               /// ����û�нӹ�
    ERR_QUEST_CONSISTENCY,                  /// �����ѱ��
    ERR_QUEST_SELECT_INDEX,                 /// ѡ�����Ʒ��������ȷ
    ERR_QUEST_ACHIEVE_TIME,                 /// �����ѳ�ʱ
    ERR_QUEST_ACHIEVE_GROUP_HUNTING,        /// ����������ּ�������
    ERR_QUEST_ACHIEVE_HUNTING,              /// ������ɴ�ּ�������
    ERR_QUEST_ACHIEVE_HUNTLEVEL,            /// ������ɴ�ȼ��ּ�������
    ERR_QUEST_ACHIEVE_GROUP_ITEM,           /// �����������Ʒ�ռ���������
    ERR_QUEST_ACHIEVE_ITEM,                 /// ���������Ʒ�ռ���������
    ERR_QUEST_ACHIEVE_APPLY_ITEM,           /// ���������Ʒʹ�ü�������
    ERR_QUEST_ACHIEVE_NPC,                  /// �������npc�ݷü�������
    ERR_QUEST_REQ_SCRIPT,                   /// ��������ű�����
    ERR_QUEST_ACHIEVE_SCRIPT,               /// ������ɽű�����
    ERR_QUEST_ACHIEVE_LEVEL,                /// ������ɵȼ�����
    ERR_QUEST_NULL,                         /// ���񲻴���
    ERR_QUEST_FORCE_READY,                  /// �����޷�ǿ�����

    //////////////////////////////////////////////////////////////////////////
    ERR_NORELIVEMAP = 2400,         /// �Ҳ��������ͼ
    ERR_ATKTOOFAST,                 /// ����Ƶ�ʹ���
    
    ERR_NOTARGET,                   // �Ҳ���Ŀ��
    ERR_NODATATYPE,                 //�޴���������

    //////////////////////////////////////////////////////////////////////////
    ERR_NPC_NOSHOP = 2500,          //�̵겻����
    ERR_NPC_NOITEM,                 //��Ʒ������
    ERR_NPC_ITEMNOENOUGH,           //��Ʒ��������
    ERR_NPC_TOOFAR,                 //����NPC̫Զ
    ERR_NPC_NO_ACCEPT,              //���겻�չ�������Ʒ
    ERR_NPC_NO_REPAIR,              /// ���겻���������Ʒ
    ERR_NPC_MUST_BIND,              /// ֻ��ʹ�ð󶨽�ҹ���
    ERR_NPC_MUST_UNBIND,            /// ֻ��ʹ�ý�ҹ���

    //////////////////////////////////////////////////////////////////////////
    ERR_MAP_ITEM_FORBID = 2600,             /// ��ͼ��ֹʹ�ô���Ʒ
    ERR_MAP_SKILL_FORBID,                   /// ��ͼ��ֹʹ�ô˼���
    ERR_MAP_RIDE_FORBID,                    /// ��ͼ��ֹʹ������

    //////////////////////////////////////////////////////////////////////////
    ERR_EXP_NOT_ENOUGH = 3000,      /// ���鲻��
    ERR_INGOT_NOT_ENOUGH,           /// Ԫ������
    ERR_BIND_INGOT_NOT_ENOUGH,      /// ��Ԫ������
    ERR_INTEGRAL_NOT_ENOUGH,        /// ���ֲ���
    ERR_GOLD_NOT_ENOUGH,            /// ��Ҳ���
    ERR_BIND_GOLD_NOT_ENOUGH,       /// �󶨽�Ҳ���
    ERR_LOCKSWITCH,                 /// �Ʋ�δ����
    ERR_OWNER_INGOT_NOT_ENOUGH,     /// ̯��Ԫ������
    ERR_OWNER_GOLD_NOT_ENOUGH,      /// ̯����Ҳ���
    ERR_NON_CURRENCY_TYPE,          /// �޴˻�������
    
    //////////////////////////////////////////////////////////////////////////
    // �ʼ�ϵͳ������
    //////////////////////////////////////////////////////////////////////////
    ERR_MAIL_MAILBOX_FULL = 3100,   /// �Է��ռ�������
    ERR_MAIL_NO_MAIL,               /// �����ڵ��ʼ�
    ERR_MAIL_NO_ATTACH,             /// û����������򸽼��Ѿ���ȡ
    ERR_MAIL_NO_PLAYER,             /// û��������
    ERR_MAIL_NOT_EMPTY,             /// �ʼ��ǿ�
    ERR_MAIL_ADD_ITEMNAME_STYLE,    /// ����ʼ��������ʹ���
    ERR_MAIL_ADD_ITEMNUM_STYLE,     /// ����ʼ���Ʒ�������ʹ���
    ERR_MAIL_ADD_ITEMBIND_STYLLE,   /// ����ʼ���Ʒ�����ʹ���
    ERR_MAIL_ADD_NON_ITERMNAME,     /// ����ʼ�����Ʒ����������
    ERR_MAIL_ADD_NUM_MORE_THAN_STACK,  /// ����ʼ�����Ʒ�����������ѵ�����
    ERR_MAIL_ADD_NONPLAYER,            /// ����ʼ��޸����
    ERR_MAIL_NON_ADDITION_INDEX,       /// ����ʼ���������������
    ERR_MAIL_ADDTION_ITEM_NUM,         /// ����ʼ�����Ʒ������������
    ERR_MAIL_NO_ADD_TYPE,              /// �޴�����ʼ�����
    ERR_MAIL_ADD_CURRENCY_TYPE,        /// ����ʼ��������ʹ���
    ERR_MAIL_ADD_CURRENCY_TYPE_NUM,    /// ����ʼ��������೬���������
    ERR_MAIL_HAD_GETED_ATTACHMENT,     /// �ʼ�����ȡ
    ERR_MAIL_NON_DEL,                  /// �ʼ��и������߻����޷�ɾ��
    ERR_MAIL_ADD_FAILED,               /// �ʼ����ʧ��
    ERR_MAIL_ATTACH_ON_INDEX_NON_ITEM, 

    //////////////////////////////////////////////////////////////////////////
    // ����ϵͳ������
    //////////////////////////////////////////////////////////////////////////
    ERR_MARKET_MAX_NUM = 3150,      /// ί�������Ѿ���������
    ERR_MARKET_MAX_COUNT,           /// ���չ���ô��������ɶ��
    ERR_MARKET_NOT_EXIST,           /// �ñʹҵ������ڻ��ѳ���
    ERR_MARKET_ITEM_MATCH,          /// �Է�û���չ�����Ʒ
    ERR_MARKET_ITEM_MUCH,           /// �Է�û���չ���ô������
    ERR_MARKET_UNIT,                /// ��Ʒ��λ������������ƥ��
    ERR_MARKET_CANT_PURCHASE,       /// �����չ�����Ʒ
    ERR_MARKET_PRICE_ERROR,         /// �ܼ۸����
    ERR_MARKET_CANT_SELL,           /// ���ܳ��۸���Ʒ
    ERR_MARKET_NOT_ENOUHG_GOLD,     /// ��Ҳ���
    ERR_MARKET_NOT_ENOUHG_INGOT,    /// Ԫ������
    //////////////////////////////////////////////////////////////////////////
    // �л������
    //////////////////////////////////////////////////////////////////////////
    ERR_FAMILY_HAS_JOINED = 3500,   /// �Է��Ѿ�������л���
    ERR_FAMILY_LOW_LEVEL,           /// ���л��м��𲻹�
    ERR_FAMILY_NO_FAMILY,           /// û�м����κ��л�
    ERR_FAMILY_OFFLINE,             /// �Է�������
    ERR_FAMILY_NOT_EXSIT,           /// ���л᲻����
    ERR_FAMILY_IN_FAMILY,           /// ���Ѿ����л���
    ERR_FAMILY_NOT_MEMBER,          /// ���Ǳ��л��Ա
    ERR_FAMILY_TITLE_NOT_EXSIT,     /// �����ڵķ��
    ERR_FAMILY_NOT_EMPTY,           /// �л��л��г�Ա����
    ERR_FAMILY_LEADER_OFFLINE,      /// �Է��᳤������
    ERR_FAMILY_HAS_ALLY,            /// �Ѿ��������л���
    ERR_FAMILY_HAS_ENEMY,           /// �Ѿ��ǵж��л���
    ERR_FAMILY_ALLY_WITH_ENEMY,     /// ���ܺ͵ж��л����
    ERR_FAMILY_ENEMY_WITH_ALLY,     /// ���Ƚ���л�����
    ERR_FAMILY_NO_ENOUGH_TITLE,     /// ��ְλ��������
    ERR_FAMILY_IS_NOT_SUBLEADER,    /// �Է����Ǹ��᳤
    ERR_FAMILY_IS_NOT_INIT,         /// �л�ϵͳ���ڳ�ʼ�������Ժ�����
    ERR_FAMILY_NAME_EXSIT,          /// �л������Ѿ����ڣ���������һ����
    ERR_FAMILY_ALLY_MAX,            /// �Ѿ��ﵽ���������л���
    ERR_FAMILY_P_ALLY_MAX,          /// �Է��Ѿ��ﵽ���������л���
    ERR_FAMILY_ENEMY_MAX,           /// �Ѿ��ﵽ���ĵж��л���
    ERR_FAMILY_LEADER_CANT_LEAVE,   /// �л�᳤���������л�
    ERR_FAMILY_TEXT_TOO_LONG,       /// �ı�������󳤶�
    ERR_FAMILY_SAME_TITLE,          /// ������Ʋ�����ͬ
    ERR_FAMILY_MAX_TITLE_MEMBER,    /// �÷�������ﵽ����
    ERR_FAMILY_MAX_MEMBER_NUM,      /// �л���������
    ERR_FAMILY_SELF,                /// ���ܺ��Լ����˻�ж�
    ERR_FAMILY_LEVEL,               /// �ȼ�����
    ERR_FAMILY_NO_RELATION,         /// �л�֮��û��ϵ
    ERR_FAMILY_CAN_NOT_TITLE,       /// title����ʧ��
    ERR_FAMILY_CAN_NOT_KICK,        /// ����ʧ��
    ERR_FAMILY_CAN_NOT_DESTORY,     /// ��ɢʧ��

    ERR_FAMILY_END,                 /// �л�����������

    //////////////////////////////////////////////////////////////////////////
    // ����С���ȴ�����
    //////////////////////////////////////////////////////////////////////////
    ERR_SPEAKER_NOT_EXIST,          ///����С���Ȳ�����

    //��ֹ��½
    ERR_FORBIDLOGIN_IP,             ///IP��ֹ��½
    ERR_FORBIDLOGIN_NAME,           ///��ɫ��ֹ��½
    ERR_FORBIDLOGIN_ACCOUNT,        ///�ʺŽ�ֹ��½
	ERR_FORBIDLOGIN_HARDWARE,		///Ӳ�����ֹ��½

    //�ɾ�
    ERR_GLORY_LEVEL,                ///�ȼ�����
    ERR_GLORY_UNFINISH,             ///�ɾ�δ���
    ERR_GLORY_HAS_AWARDED,          ///�����Ѿ���ȡ


    //����
    ERR_MONSTER_ALLOC,              ///����Monster*ʧ��
    ERR_MONSTER_BORNPOS,            ///����û�г�����
    ERR_MONSTER_APPEAR,             ///������ְ�����
    ERR_MONSTER_NOTMAP,              ///����û�е�ͼ��Ϣ
    ERR_MONSTER_NOTCONFIG,           ///����û��ģ����Ϣ

    //�û�ָ��
    ERR_UCMD_OK,                    ///�û�ָ��ִ�гɹ�
    ERR_UCMD_FAIL,                  ///�û�ָ��ִ��ʧ��

    //
    ERR_MIGRATE_IN_DEAL,            ///ͬ�˺���һ������Ǩ�ƴ�����
    ERR_MIGRATE_TIMEOUT,            ///����Ǩ�Ƴ�ʱ
    ERR_MIGRATE_LOGIC,              ///����Ǩ���߼�����
    ERR_MIGRATE_NO_MD,              ///����Ǩ��������ת������ʧ��
    ERR_MIGRATE_NO_DST,             ///����Ǩ������Ŀ����������ʧ��
    ERR_MIGRATE_NO_ACK,             ///����Ǩ��Ŀ������Ӧ��
    ERR_MIGRATE_AGENT,              ///����Ǩ��ֻ����ͬһ���������֮��
    ERR_MIGRATE_TYPE,               ///����Ǩ��ֻ���ڲ���������ʽ��֮��
    ERR_MIGRATE_SVR_INFO,           ///����Ǩ���Ҳ���Ŀ������������Ϣ
    ERR_FAMILY_NO_JOIN_REQUEST,     ///û�м����л������

    //////////////////////////////////////////////////////////////////////////
    // �ڹ�
    //////////////////////////////////////////////////////////////////////////
    ERR_INNER_FORCE_LEVEL_UP_FAILED,    ///�ڹ�����ʧ��

    ERR_MOBA_NO_VALID_ROOM_ID = 3600,   /// �޿��õķ����
    ERR_MOBA_ALREADY_IN_ROOM,           /// �Ѿ��ڷ�����
    ERR_MOBA_NO_ROOM,                   /// ���䲻����
    ERR_MOBA_MAX_ROOM_MEMBER,           /// ������������
    ERR_MOBA_ROOM_PWD,                  /// �����������
    ERR_MOBA_ROOM_NAME_DUPLICATE,       /// ���������ظ�
    ERR_MOBA_INVALID_ROOM_OP,           /// �Ƿ��ķ������
    ERR_MOBA_ROOM_STATE_CANT_OP,        /// �˷���״̬�²��ܽ��иò���
    ERR_MOBA_ROOM_MEMBER_NOT_EXIST,     /// �����Ա������
    ERR_MOBA_SET_VICE_HOST,             /// ֻ�������Է���Ӫ���Ϊ������
    ERR_MOBA_ROOM_MODE,                 /// ����ģʽ����
    ERR_MOBA_ROOM_VS_NUM,               /// �����ս��������
    ERR_MOBA_ALREADY_IN_GAME,           /// �˷����Ѿ�����Ϸ��

    ERR_SERVER_STATUS = 3800,
    ERR_SERVER_STATUS_MAINTENANCE,  /// ά��

    //����
    ERR_CHANGE_NAME_REPEAT = 3900,      /// �����ظ�
    ERR_CHANGE_NAME_NOT_EXIST,          /// ��Ҳ�����
    ERR_CHANGE_NAME_ILLEGAL_CHARACTERS, /// ���ֺ��Ƿ��ַ�

    //�ƺ�
    ERR_TITLE_DEL_ERR = 4000,   /// �ƺ�ɾ��ʧ��

    //���ڴ���֮����Ӵ�����
    ERR_COUNT,
};
