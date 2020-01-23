#ifndef KIBBOMI_SCORE
#define KIBBOMI_SCORE

#include "Point.h"

class Score 
{
public :
    Score();                                                // score_ 값을 0으로 초기화
    void UpdateScore(Point reference_pos, int increment);   // Increment 만큼 점수를 더해 줌
    void Print(Point reference_pos);                        // 점수 출력 위치에 점수 출력
	int GetScore(void) { return score_; }
	static void ReadRanking(void);
	void SaveRanking(Point reference_pos, int score_);
private :
    int score_;
    Point score_pos_;
};

#endif