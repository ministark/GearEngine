#include "GearSprites.h"



void GearSprite::Remove()
{
	markForDeletion = true;
}

GearSprite::GearSprite(LPDIRECT3DDEVICE9 D3ddev, float width, float height, std::string image)
{
	markForDeletion = 0;
	d3ddev = D3ddev;

	vertices[0] = { -(width / 2), -(height / 2), 0.0f, D3DCOLOR_XRGB(255, 255, 255),0.99f,0.99f };
	vertices[1] = {  (width / 2), -(height / 2), 0.0f, D3DCOLOR_XRGB(255, 255, 255),0.01f,0.99f };
	vertices[2] = { -(width / 2),  (height / 2), 0.0f, D3DCOLOR_XRGB(255, 255, 255),0.99f,0.01f };
	vertices[3] = {  (width / 2),  (height / 2), 0.0f, D3DCOLOR_XRGB(255, 255, 255),0.01f,0.01f };

	// create a vertex buffer interface called v_buffer
	d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),0,CUSTOMFVF,D3DPOOL_MANAGED,&v_buffer,NULL);
	d3ddev->CreateIndexBuffer(6 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &i_buffer, NULL);

	VOID* vVoid,* iVoid;    // a void pointer
	// lock v_buffer and load the vertices into it
	v_buffer->Lock(0, 4*sizeof(CUSTOMVERTEX), &vVoid, 0);
	memcpy(vVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();
	// Load the indices
	i_buffer->Lock(0, 6 * sizeof(short), &iVoid, 0);
	memcpy(iVoid, (void*)indices, 6*sizeof(short));
	i_buffer->Unlock();

	D3DXCreateTextureFromFile(d3ddev, image.c_str(), &g_texture);
	d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void GearSprite::Render(float x, float y)
{
	d3ddev->SetFVF(CUSTOMFVF);

	// Transforming the sprite
	D3DXMATRIX matTransform;
	D3DXMatrixTranslation(&matTransform, x, y, 0);

	D3DXMATRIX matRotateY;    // a matrix to store the rotation information
	static float index = 0.0f; index += 0.0f;    // an ever-increasing float value
	// build a matrix to rotate the model based on the increasing float value
	D3DXMatrixRotationY(&matRotateY, index);

	// tell Direct3D about our matrix
	d3ddev->SetTransform(D3DTS_WORLD, &(matRotateY*matTransform));
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(i_buffer);

	// Setting Texture
	d3ddev->SetTexture(0, g_texture);
	// copy the vertex buffer to the back buffer
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

}

void GearSprite::Clean()
{
	v_buffer->Release();
}


GearSprite::~GearSprite()
{
	v_buffer->Release();;
}
