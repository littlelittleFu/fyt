#include"CSocket.h"

void CSocket::OnSend(UINT len)
{

}

void CSocket::OnRecv(UINT len)
{
	// �ж��Ƿ�������


	if (nullptr == m_RecvBuf)
	{
		m_RecvPos += len;

		// ���ջ������� ����û���յ���ɰ�
		if (m_RecvPos > m_RecvSize)
		{
			std::cout << "������������ջ�������" << std::endl;
			return;
		}

		while (true)
		{
			// ��δ��������Ϣͷ
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

			//��δ������Ϣ��
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
	// �ж��Ƿ�������
	bool _Ret = false;

	if ((nullptr != m_RecvBuf) && (m_RecvPos < m_RecvSize)) {
		_Ret = true;
		ZeroMemory(&m_IoDataRecv.overlapped, sizeof(m_IoDataRecv.overlapped));
		m_IoDataRecv.wsabuf->buf = m_RecvBuf + m_RecvPos;
		m_IoDataRecv.wsabuf->len = m_RecvSize - m_RecvPos;

		DWORD _Len = 0, _Flag = 0;
		if (0 != WSARecv(m_Socket, m_IoDataRecv.wsabuf, 1, &_Len, &_Flag, &m_IoDataRecv.overlapped, nullptr)) {
			std::cout << "������Ϣʧ�ܣ�" << std::endl;
		}
	}
	return _Ret;
}