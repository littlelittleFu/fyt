#include"CSocket.h"

void CSocket::OnSend(UINT len)
{

}

void CSocket::OnRecv(UINT len)
{
	// 判断是否连接中


	if (nullptr == m_RecvBuf)
	{
		m_RecvPos += len;

		// 接收缓冲区满 但是没有收到完成包
		if (m_RecvPos > m_RecvSize)
		{
			std::cout << "包体大于最大接收缓冲区！" << std::endl;
			return;
		}

		while (true)
		{
			// 还未接收完消息头
			if (m_RecvPos < sizeof(UINT)) {
				PostRecv();
				return;
			}

			UINT _MsgLen = *(UINT*)m_RecvBuf;

			if (_MsgLen < sizeof(UINT)) {
				m_RecvPos = 0;
				PostRecv();
				return;
			}

			//还未收完消息体
			if (m_RecvPos < _MsgLen) {
				PostRecv();
				return;
			}

			DATA_CACHE& _Cache = m_RecvDataCache;
			_Cache._Data = nullptr;
			_Cache._MaxLen = _MsgLen - sizeof(UINT);
			_Cache._Len = _MsgLen - sizeof(UINT);

		}
	}
}



bool CSocket::PostRecv()
{
	// 判断是否连接中
	bool _Ret = false;

	if ((nullptr != m_RecvBuf) && (m_RecvPos < m_RecvSize)) {
		_Ret = true;
		ZeroMemory(&m_IoDataRecv.overlapped, sizeof(m_IoDataRecv.overlapped));
		m_IoDataRecv.wsabuf->buf = m_RecvBuf + m_RecvPos;
		m_IoDataRecv.wsabuf->len = m_RecvSize - m_RecvPos;

		DWORD _Len = 0, _Flag = 0;
		if (0 != WSARecv(m_Socket, m_IoDataRecv.wsabuf, 1, &_Len, &_Flag, &m_IoDataRecv.overlapped, nullptr)) {
			std::cout << "接收消息失败！" << std::endl;
		}
	}
	return _Ret;
}