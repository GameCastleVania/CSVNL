#include "sprite.h"
#include "keyboard.h"

class HealthBar :
	public Sprite
{
private:
	int bosshealth;
	int emptybosshealth;
	int emptysimonhealth;
	int simonhealth;
	int maxhealth;

	bool Zpress = false;
	bool Xpress = false;
	bool Cpress = false;
	bool Vpress = false;

	Sprite* axeitem;
	Sprite* bmritem;
	Sprite* daggeritem;
	Sprite* fbombitem;
	Sprite* healthbar;
	Keyboard* kbd;

public:
	HealthBar();
	~HealthBar();
	HealthBar(LPDIRECT3DDEVICE9 _d3ddv, float x, float y, int vpx, int vpy, Keyboard* kbd);

	void Update();
	void Draw(int vpx, int vpy);
	void Render(int vpx, int vpy);

};