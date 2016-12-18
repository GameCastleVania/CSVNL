#include "sprite.h"

extern float SimonHP;

class HealthBar :
	public Sprite
{
private:
	int bosshealth;
	int emptybosshealth;
	int emptysimonhealth;
	int simonhealth;
	int maxhealth;

	Sprite* healthbar;

public:
	HealthBar();
	~HealthBar();
	HealthBar(LPDIRECT3DDEVICE9 _d3ddv, float x, float y, int vpx, int vpy);

	void Update(int bosshealth);
	void Draw(int vpx, int vpy);
	void Render(int vpx, int vpy);

};