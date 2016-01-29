
#include "TDNLIB.h"

tdnMesh::tdnMesh() : decl( nullptr ), declSize( 0 ), vertexBuffer( nullptr ), numVertexes( 0 ), indexBuffer( nullptr ), numIndexes( 0 ), numFaces( 0 )
{
	D3DXMatrixIdentity( &worldMatrix );
}
tdnMesh::~tdnMesh()
{
	decl->Release();
	vertexBuffer->Release();
	indexBuffer->Release();
}

bool tdnMesh::CreateVertex( unsigned int numVertexes, unsigned int vertexSize, void *vertexArray )
{
	HRESULT hr( S_OK );

	// ���_�z��̃T�C�Y�v�Z
	unsigned int vertexesSize = vertexSize * numVertexes;
	this->numVertexes = numVertexes;

	// �o�b�t�@new
	hr = tdnSystem::GetDevice()->CreateVertexBuffer(
		vertexesSize,    // ���_�z��̃o�C�g��
		0,               // �g�p���@ D3DUSAGE
		D3DFVF_XYZ,      // ?
		D3DPOOL_MANAGED, // ?
		&vertexBuffer,   // ���_�o�b�t�@ <out>
		0 );             // ?
	if( FAILED( hr ) )
		return false;

	// �o�b�t�@�ɃR�s�[
	Vector3* workVertex( nullptr );
	hr = vertexBuffer->Lock( 0, 0, ( void** ) &workVertex, 0 );      // �o�b�t�@���b�N (�o�t�@�̃|�C���^�[�擾)
	if( FAILED( hr ) )
		return false;
	memcpy_s( workVertex, vertexesSize, vertexArray, vertexesSize ); // �o�b�t�@�ɒ��_�����R�s�[
	hr = vertexBuffer->Unlock();                                     // �o�b�t�@���b�N������
	if( FAILED( hr ) )
		return false;

	return true;
}
bool tdnMesh::CreateIndexes( unsigned int numIndexes, const DWORD *indexArray )
{
	HRESULT hr( S_OK );

	this->numIndexes = numIndexes;

	// �C���f�b�N�X�z��̃T�C�Y�v�Z
	unsigned int indexesSize = sizeof( DWORD ) * numIndexes;
	// �C���f�b�N�Xnew
	hr = tdnSystem::GetDevice()->CreateIndexBuffer(
		indexesSize,     // �C���f�b�N�X�z��̃o�C�g��
		0,               // �g�p���@ D3DUSAGE
		D3DFMT_INDEX32,  // �t�H�[�}�b�g
		D3DPOOL_MANAGED, // ?
		&indexBuffer,    // �C���f�b�N�X�o�b�t�@ <out>
		NULL );          // ?
	if( FAILED( hr ) )
		return false;

	// �o�b�t�@�ɃR�s�[
	DWORD* workIndex( nullptr );
	hr = indexBuffer->Lock( 0, 0, ( void** ) &workIndex, 0 );    // �o�b�t�@���b�N (�o�t�@�̃|�C���^�[�擾)
	if( FAILED( hr ) )
		return false;
	memcpy_s( workIndex, indexesSize, indexArray, indexesSize ); // �o�b�t�@�ɃC���f�b�N�X�����R�s�[
	hr = indexBuffer->Unlock();                                  // �o�b�t�@���b�N������
	if( FAILED( hr ) )
		return false;

	return true;
}
bool tdnMesh::CreateDeclaration( unsigned int declSize, D3DVERTEXELEMENT9 *decl )
{
	HRESULT hr( S_OK );

	this->declSize = declSize;
	//FVF�쐬
	hr = tdnSystem::GetDevice()->CreateVertexDeclaration( decl, &this->decl );
	if( FAILED( hr ) )
		return false;

	return true;
}
bool tdnMesh::Create( const CreateData &data )
{
	if( CreateVertex( data.numVertexes, data.vertexSize, data.vertexArray ) == false )
		return false;
	if( CreateIndexes( data.numIndexes, data.indexArray ) == false )
		return false;
	if( CreateDeclaration( data.vertexSize, data.decl ) == false )
		return false;
	return true;
}

bool tdnMesh::CreateTriangle( float radius, DWORD color )
{
	CreateData data;
	float rad120( PI * 2 / 3 );
	float s( sinf( rad120 ) ), c( cosf( rad120 ) );
	VECTOR_LINE vertexArray[]
	{
		{ -s*radius, c*radius, 0, color },
		{ 0, radius, 0, color },
		{ s*radius, c*radius, 0, color }
	};
	data.vertexArray = vertexArray;
	data.vertexSize = sizeof( VECTOR_LINE );
	data.numVertexes = ARRAYSIZE( vertexArray );

	DWORD indexArray[]
	{
		0, 1, 2
	};
	data.indexArray = indexArray;
	data.numIndexes = ARRAYSIZE( indexArray );

	D3DVERTEXELEMENT9 declAry[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, sizeof(Vector3), D3DDECLTYPE_UBYTE4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	data.decl = declAry;

	numFaces = data.numIndexes / 3;

	return Create( data );
}
bool tdnMesh::CreateRectangle( float width, float height, DWORD color )
{
	CreateData data;
	width *= 0.5f;
	height *= 0.5f;
	VECTOR_LINE vertexArray[]
	{
		{ -width, -height, 0, color},
		{ -width, height, 0, color },
		{ width, -height, 0, color },
		{ width, height, 0, color }
	};
	data.vertexArray = vertexArray;
	data.vertexSize = sizeof( VECTOR_LINE );
	data.numVertexes = ARRAYSIZE( vertexArray );

	DWORD indexArray[]
	{
		0, 1, 2,
			1, 3, 2
	};
	data.indexArray = indexArray;
	data.numIndexes = ARRAYSIZE( indexArray );

	D3DVERTEXELEMENT9 declAry[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, sizeof( Vector3 ), D3DDECLTYPE_UBYTE4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	data.decl = declAry;

	numFaces = data.numIndexes / 3;

	return Create( data );
}
bool tdnMesh::CreateTriangular( float radius, DWORD color )
{
	CreateData data;
	float rad120( PI * 2 / 3 );
	float s( sinf( rad120 ) ), c( cosf( rad120 ) );
	VECTOR_LINE vertexArray[]
	{
		{0, radius, 0, color},
		{ 0, c*radius, radius, color },
		{ -s*radius, c*radius, c*radius, color },
		{ s*radius, c*radius, c*radius, color }
	};
	data.vertexArray = vertexArray;
	data.vertexSize = sizeof( VECTOR_LINE );
	data.numVertexes = ARRAYSIZE( vertexArray );

	DWORD indexArray[]
	{
		0, 3, 2,
			0, 1, 3,
			0, 2, 1,
			1, 2, 3,
	};
	data.indexArray = indexArray;
	data.numIndexes = ARRAYSIZE( indexArray );

	D3DVERTEXELEMENT9 declAry[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, sizeof( Vector3 ), D3DDECLTYPE_UBYTE4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	data.decl = declAry;

	numFaces = data.numIndexes / 3;

	return Create( data );
}
bool tdnMesh::CreateCube( float width, float height, float depth, DWORD color )
{
	CreateData data;
	width *= 0.5f;
	height *= 0.5f;
	depth *= 0.5f;
	VECTOR_LINE vertexArray[]
	{
		{ -width, -height, -depth, color},
		{ -width, -height, depth, color },
		{ -width, height, -depth, color },
		{ -width, height, depth, color },
		{ width, -height, -depth, color },
		{ width, -height, depth, color },
		{ width, height, -depth, color },
		{ width, height, depth, color }
	};
	data.vertexArray = vertexArray;
	data.vertexSize = sizeof( VECTOR_LINE );
	data.numVertexes = ARRAYSIZE( vertexArray );

	DWORD indexArray[]
	{
		0, 2, 6,
			0, 6, 4,
			4, 6, 7,
			4, 7, 5,
			3, 5, 7,
			1, 5, 3,
			1, 3, 2,
			2, 0, 1,
			0, 4, 1,
			4, 5, 1,
			2, 3, 7,
			7, 6, 2
	};
	data.indexArray = indexArray;
	data.numIndexes = ARRAYSIZE( indexArray );

	D3DVERTEXELEMENT9 declAry[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, sizeof( Vector3 ), D3DDECLTYPE_UBYTE4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	data.decl = declAry;

	numFaces = data.numIndexes / 3;

	return Create( data );
}

void tdnMesh::Render( tdnShader *shader, char *technique )
{
	unsigned int numPass = shader->Begin( technique );

	shader->SetValue( "worldMatrix", worldMatrix );

	//�g�p�X�g���[���w��ƒ��_�o�b�t�@�ݒ�
	tdnSystem::GetDevice()->SetStreamSource( 0, vertexBuffer, 0, declSize );
	//���_�C���f�b�N�X�w��
	tdnSystem::GetDevice()->SetIndices( indexBuffer );
	//���_�\���̎w��
	tdnSystem::GetDevice()->SetVertexDeclaration( decl );
	for( unsigned int i = 0; i < numPass; i++ )
	{
		shader->BeginPass( i );

		//�`��(�ʓ�ƂO����n�܂钸�_�Ǝw��)
		tdnSystem::GetDevice()->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0, //�J�n�n�_����̑��Έʒu
			0, //�ŏ��C���f�b�N�X�ԍ�
			numIndexes, //�ő�C���f�b�N�X�ԍ�
			0, //�C���f�b�N�X�z��̓ǂݎ��ʒu	
			numFaces //�ʂ̐�
			);

		shader->EndPass();
	}

	shader->End();
}
