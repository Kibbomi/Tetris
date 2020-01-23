#ifndef KIBBOMI_SCORE
#define KIBBOMI_SCORE

#include "Point.h"

class Score 
{
public :
    Score();                                                // score_ ���� 0���� �ʱ�ȭ
    void UpdateScore(Point reference_pos, int increment);   // Increment ��ŭ ������ ���� ��
    void Print(Point reference_pos);                        // ���� ��� ��ġ�� ���� ���
	int GetScore(void) { return score_; }
	static void ReadRanking(void);
	void SaveRanking(Point reference_pos, int score_);
private :
    int score_;
    Point score_pos_;
};

#endif