/*******************************************************************************
 * Project:  Nebula
 * @file     CmdOnSetNodeConf.hpp
 * @brief    设置节点信息
 * @author   Bwar
 * @date:    2019年9月14日
 * @note
 * Modify history:
 ******************************************************************************/

#ifndef SRC_ACTOR_CMD_SYS_CMD_MANAGER_CMDONSETNODECONF_HPP_
#define SRC_ACTOR_CMD_SYS_CMD_MANAGER_CMDONSETNODECONF_HPP_

#include "actor/ActorSys.hpp"
#include "actor/cmd/Cmd.hpp"

namespace neb
{

class SessionManager;

class CmdOnSetNodeConf: public Cmd,
    public DynamicCreator<CmdOnSetNodeConf, int32>, public ActorSys
{
public:
    CmdOnSetNodeConf(int32 iCmd);
    virtual ~CmdOnSetNodeConf();
    virtual bool AnyMessage(
                    std::shared_ptr<SocketChannel> pChannel,
                    const MsgHead& oMsgHead,
                    const MsgBody& oMsgBody);

private:
    std::shared_ptr<SessionManager> m_pSessionManager;
    std::string m_strDataString;
};

} /* namespace neb */

#endif /* SRC_ACTOR_CMD_SYS_CMD_MANAGER_CMDONSETNODECONF_HPP_ */

