#include "Model.h"


Model::Model()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texture = 0;
}

Model::Model(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Model::Model(const Model& other)
{
	
}

Model::~Model()
{
}

bool Model::Initialize(ID3D11Device* device, Texture* texture)
{
	myDevice = device;
	bool result;
	result = InitializeBuffers(device);
	if (!result) return false;
	m_texture = texture;

	return true;
}

void Model::Shutdown()
{
	//ReleaseTexture();
	ShutdownBuffers();
}

void Model::Render(ID3D11DeviceContext* deviceContext)
{
	UpdateBuffers(myDevice);
	// put the vertex and index buffers on a graphics pipeline to prepare them for drawing
	RenderBuffers(deviceContext);
}

int Model::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* Model::GetTexture()
{
	return m_texture->GetTexture();
}

Model::VertexIndex* Model::LoadGeometry()
{
	Vertex* vertices;
	unsigned long* indices;
	
	m_vertexCount = 3;
	m_indexCount = 3;

	vertices = new Vertex[m_vertexCount];
	indices = new unsigned long[m_indexCount];

	// load vertex array with data
	// texture coords
	vertices[0].position = D3DXVECTOR3(-1.0f*scale.x, -1.0f*scale.y, 0.0f*scale.z) + position; // BL
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[1].position = D3DXVECTOR3(-1.0f*scale.x, 1.0f*scale.y, 0.0f*scale.z) + position; // TL
	vertices[1].texture = D3DXVECTOR2(0.0f, 1.0f);
	vertices[2].position = D3DXVECTOR3(1.0f*scale.x, -1.0f*scale.y, 0.0f*scale.z) + position; // BR
	vertices[2].texture = D3DXVECTOR2(1.0f, 0.0f);

	// load index array with data
	indices[0] = 0; // BL
	indices[1] = 1; // TL
	indices[2] = 2; // BR

	VertexIndex* toReturn = new VertexIndex;
	toReturn->vertexArrayPtr = vertices;
	toReturn->indexArrayPtr = indices;
	return toReturn;
}

bool Model::InitializeBuffers(ID3D11Device* device)
{
	Vertex* vertices = nullptr;
	unsigned long* indices = nullptr;
	HRESULT result;

	VertexIndex* set = LoadGeometry();
	vertices = set->vertexArrayPtr;
	indices = set->indexArrayPtr;

	// setup description of static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// create vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result)) return  false;

	// as above / index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result)) return false;

	/////

	delete[] vertices;
	vertices = nullptr;
	delete[] indices;
	indices = nullptr;
	delete set;

	return true;
}

void Model::UpdateBuffers(ID3D11Device* device)
{
	m_indexBuffer->Release();
	m_vertexBuffer->Release();

	Vertex* vertices = nullptr;
	unsigned long* indices = nullptr;
	
	HRESULT result;

	VertexIndex* set = LoadGeometry();
	vertices = set->vertexArrayPtr;
	indices = set->indexArrayPtr;

	// give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// create vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);

	/////

	delete[] vertices;
	vertices = nullptr;
	delete[] indices;
	indices = nullptr;
	delete set;
}

void Model::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
}

void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride, offset;

	// vertex buffer stride and offset
	stride = sizeof(Vertex);
	offset = 0;

	// set vertex buffer to active in the input assembler so it can be rendered
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// as above, with index buffer
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// set type of a primitive that should be drawn !!!!!!!!!!!!!
	deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	string debug = to_string(rotation.z) + "\n";
}

bool Model::LoadTexture(ID3D11Device* device, LPCSTR filename)
{
	bool result;

	m_texture = new Texture();
	if (!m_texture) return false;

	result = m_texture->Initialize(device, filename);
	if (!result) return false;
	return true;
}

void Model::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = nullptr;
	}
}
