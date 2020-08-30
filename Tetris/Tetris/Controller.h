#ifndef KIBBOMI_CONTROLLER
#define KIBBOMI_CONTROLLER

#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_UP (256 + 72)
#define KEY_DOWN (256 + 80)
#define KEY_LEFT (256 + 75)
#define KEY_RIGHT (256 + 77)
#define KEY_SPACE 32
#define KEY_SAVE 99

class Controller
{
public:
	void SetController(int key_esc, int key_right, int key_left, int key_rotate, int key_down, int key_space, int key_savetetromino);
	int Getkey_esc() { return key_esc_; }
	int Getkey_right() { return key_right_; }
	int Getkey_left() { return key_left_; }
	int Getkey_rotate() { return key_rotate_; }
	int Getkey_down() { return key_down_; }
	int Getkey_space() { return key_space_; }
	int Getkey_savetetromino() { return key_savetetromino_; }

	static int GetKey();    // ���� �Էµ� Ű �˾ƿ���

private:
	int key_esc_;           // ��Ʈ���� ����
	int key_right_;         // ���������� �̵�
	int key_left_;          // �������� �̵�
	int key_rotate_;        // ȸ��
	int key_down_;          // �� ĭ ��������
	int key_space_;			// �ѹ��� ��������
	int key_savetetromino_;	//����
};

#endif