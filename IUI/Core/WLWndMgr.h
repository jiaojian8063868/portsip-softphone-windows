// CWLWnd������
// �������CWLWnd�Ĵ�������ʹCWLWnd�����ݼ��ӿؼ���������λ��Ʋ���CWLWnd���棻
// ��ʹ��CWLWnd::SetWindowRgn�����˲ü������CWLWnd�����ݼ��ӿؼ��������ܻ��Ƶ��ü�����
// �����档 �������ҲҪ�޶�����������ڡ� ����Щ��������Ӧ����CWLWnd������Ҫ���ĵģ�CWLWnd����
// ʱ���ü�����Ӧ���Ѿ���ɣ�CWLWnd���в���ʱ��Ҳ��Ӧ�ÿ�����SetWindowRgn����£���SetWindowRgn
// ���棬�Ͳ�Ӧ���յ������Ϣ�����������յ������Ϣ�����ж��Ƿ���SetWindowRgn�ڲ���

#pragma once


namespace CWLWndMgr
{
	// ����CWLWndΪ�༭ģʽ�� ��CWLWnd���ڽ���༭��ʱ���������CWLWnd����ӿؼ���Ҳ����ͨ��
	// ������̲����ӿؼ��� �������Ӧ��ȥ������Ϊ��ΪCWLWnd����������ΪEditģʽ�ṩ����֧�֡�
	// һ������������CWLWnd���û�Ӧ��ͨ�����ṩ�Ľӿڣ�����֧��Editģʽ��Ҫ�����й��ܡ�
	// ���磺�û�ͨ�����ϲ㴦��Button��WM_CREATE��Ϣ������ֹComboBox��Button�ӿؼ�����
	// ������ͨ��ΪComboBox���ó�Editģʽ����ֹButton�ӿؼ�������
	int SetEditMode(HWLWND hWnd, BOOL bEditMode);
	BOOL IsEditMode(HWLWND hWnd);


	// �ڻ���CWLWndǰ��ҪΪCWLWnd���òü����򣬷�ֹ���ݻ��ӿؼ����Ƶ�CWLWnd�⡣
	// ���ڸ��Ӵ��ڶ��ǻ��Ƶ�ͬһ��HDC�ϣ��ڸ��ؼ�����ǰ����HRGN���óɸ��ؼ�һ����С
	// �ں��ӻ���ǰ���������óɺ��Ӵ�С����Ϊ���ӿ����в��ֻ�ȫ��λ�ø��ؼ�֮�⡣
	// Ӧ�ðѸ��ؼ���HRGN���ӿؼ���λ�á��ӿؼ�SetWindowRgn���õ�HRGN�������������Ϊ�ӿؼ���
	// bClientArea��TRUE: ֻ���ƿͻ������ǿͻ������õ���
	int SetClip(HWLWND hCtrl, HDC hDC, BOOL bClientArea);

} // namespace CWLWndMgr
