#pragma once

class GameScene : public eel::Scene, public eel::MakeCreate<GameScene>
{
public:
	GameScene();
	~GameScene() override = default;

private:
};