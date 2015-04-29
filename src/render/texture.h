#include "d3dx11Effect.h"
#include "base/object.h"
#include "utility/makeCreate.h"

NS_EEL_BEGIN

class Texture : public Object, public MakeCreate<Texture>
{
public:
	Texture(float width, float height);
	~Texture() override;

	operator ID3D11Texture2D*();

private:
	ID3D11Texture2D* m_Texture = nullptr;
};

NS_EEL_END