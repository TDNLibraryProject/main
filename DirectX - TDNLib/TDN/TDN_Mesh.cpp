
#include "TDNLIB.h"
#include <fstream>
#include <string>
#include <vector>

tdnMesh::tdnMesh() : decl( nullptr ), declSize( 0 ), vertexBuffer( nullptr ), numVertexes( 0 ), indexBuffer( nullptr ), numIndexes( 0 ), numFaces( 0 ), pos( 0, 0, 0 ), scale( 1, 1, 1 ), rot( 0, 0, 0, 1 )
{
	D3DXMatrixIdentity( &worldMatrix );
}
tdnMesh::~tdnMesh()
{
	decl->Release();
	vertexBuffer->Release();
	indexBuffer->Release();
}

/********/
/* �쐬 */
/********/

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

/************/
/* �ǂݍ��� */
/************/

template<class TYPE_FSTREAM> bool OpenFstream( TYPE_FSTREAM *out, char *filename )
{
	out->open( filename );
	if( out->fail() ) // �J���Ȃ�����
	{
		char text[256] = {};
		sprintf_s( text, "%s ���J���܂���", filename );
		MessageBox( NULL, text, "�G���[", 0 );
		return false;
	}
	return true;
}

// MQO�t�@�C��

class MqoLoadObject
{
public:
	virtual void Load( std::ifstream &mqoFile ) = 0;

protected:
	// �֐��|�C���^�̖߂�l
	enum class FPCODE : byte
	{
		FAILURE, SUCCESS, END
	};

	// "" �ň͂܂ꂽ������ǂݍ���
	inline void LoadName(
		std::ifstream &mqoFile,
		std::string &name )
	{
		mqoFile >> name;
		name = name.substr( 1, name.size() - 2 ); // �O��� " " ������
	}

	// type �̔z���ǂݍ���
	template
		<
			class type,
				size_t size
		>
		inline FPCODE LoadArray(
		std::ifstream &mqoFile,
		std::string& load,
		const std::string& com,
		type( &out )[size]
		)
			{
				if( load == "}" )
					return FPCODE::END;

				if( load != com )
					return FPCODE::FAILURE;

				for( size_t i = 0; i < size; i++ )
				{
					mqoFile >> out[i];
				}
				return FPCODE::SUCCESS;
			}

	// com(float) �̌`�̕������ǂݍ���float�����o��
	inline FPCODE LoadFloatParenthesi(
		std::string& load,
		const std::string com, // �ϐ��̖��O
		float* out
		)
	{
		if( load == "}" )
			return FPCODE::END;

		if( load.substr( 0, com.size() ) != com )
			return FPCODE::FAILURE;

		*out = stof( load.substr( com.size() + 1 ) ); // ���������o��
		return FPCODE::SUCCESS;
	}

	// com("string") �̌`�̕������ǂݍ���string�����o��
	inline FPCODE LoadStringParenthesi(
		std::string& load,
		const std::string com, // �ϐ��̖��O
		std::string* out
		)
	{
		if( load == "}" )
			return FPCODE::END;

		if( load.substr( 0, com.size() ) != com )
			return FPCODE::FAILURE;

		*out = load.substr( com.size() + 2, load.size() - com.size() - 4 ); // ���������o��
		return FPCODE::SUCCESS;
	}

	// com(type type ...) �̌`�̕������ǂݍ���type�̔z������o��
	template<
		class type,
			size_t size
	>
	inline FPCODE LoadArrayParenthesi(
	std::ifstream& mqoFile,
	std::string& load,
	const std::string com, // �ϐ��̖��O
	type( &out )[size]
	)
		{
			if( load == "}" )
				return FPCODE::END;

			if( load.substr( 0, com.size()) != com )
				return FPCODE::FAILURE;

			out[0] = stof( load.substr( com.size() + 1 ) ); // ���������o��
			for( size_t i = 1; i < size; i++ )
			{
				mqoFile >> out[i];
			}
			std::string workString;
			mqoFile >> workString; // ")" ��ǂ�
			return FPCODE::SUCCESS;
		}

	// �֐��|�C���^�[�̔z�����
	template<class LoadObjectClass>
	void LoadLoop(
		LoadObjectClass* me,
		std::ifstream &mqoFile,
		FPCODE( LoadObjectClass::*loadFP[] )( std::ifstream&, std::string& load ),
		unsigned int numFP
		)
	{
		for( unsigned int step( 0 ); step < numFP; )
		{
			std::string workString;
			mqoFile >> workString;
			if( mqoFile.eof() )
				break;

			for( unsigned int i = step; i < numFP; i++ )
			{
				switch( ( me->*loadFP[i] )( mqoFile, workString ) )
				{
					case FPCODE::FAILURE:
						break;

					case FPCODE::SUCCESS:
						step = i;
						i = numFP;
						break;

					case FPCODE::END:
						step = numFP;
						i = numFP;
						break;
				}
			}
		}
	}
};

class MqoMaterial : public MqoLoadObject
{
public:
	std::string name;    // �ގ���       31byte�ȓ�
	float col[4];        // ���_�F RGBA  0~1
	float dif;           // �g�U��       0~1
	float amb;           // ���͌�       0~1
	float emi;           // ���ȏƖ�     0~1
	float spc;           // ���ˌ�       0~1
	float power;         // ���ˌ��̋��� 0~100
	float reflect;       // ���ʔ���     0~1
	float refract;       // ���ܗ�       1~5
	std::string tex;     // �͗l�e�N�X�`��
	std::string aplane;  // �����e�N�X�`��
	std::string bump;    // ���ʃe�N�X�`��
	float proj_pos[3];   // �ʒu XYZ
	float proj_scale[3]; // �g�嗦 XYZ
	float proj_angle[3]; // �p�x YXZ     -180~180

	MqoMaterial() : dif(0), amb(0), emi(0), spc(0), power(0), reflect(0), refract(0)
	{
		col[0] = col[1] = col[2] = col[3] = 1;
		proj_pos[0] = proj_pos[1] = proj_pos[2] = 0;
		proj_scale[0] = proj_scale[1] = proj_scale[2] = 1;
		proj_angle[0] = proj_angle[1] = proj_angle[2] = 0;
	}

	void Load( std::ifstream &mqoFile )
	{
		std::string workString;
		mqoFile >> workString; // { ��ǂ�
		LoadName( mqoFile, name );

		// �ϐ���ǂݍ��ފ֐�
		FPCODE( MqoMaterial::*loadFP[] )( std::ifstream &mqoFile, std::string& load )
		{
			&MqoMaterial::LaodCol, &MqoMaterial::LoadDif, &MqoMaterial::LoadAmb, &MqoMaterial::LoadEmi, &MqoMaterial::LoadSpc, &MqoMaterial::LoadPower, &MqoMaterial::LoadReflect, &MqoMaterial::LoadRefract, &MqoMaterial::LoadTex, &MqoMaterial::LoadAplane, &MqoMaterial::LoadBump, &MqoMaterial::LaodProj_pos, &MqoMaterial::LaodProj_scale, &MqoMaterial::Laodproj_angle
		};

		LoadLoop<MqoMaterial>( this, mqoFile, loadFP, ARRAYSIZE( loadFP ) );
	}

private:
	FPCODE LaodCol( std::ifstream &mqoFile, std::string& load )
	{
		return LoadArrayParenthesi( mqoFile, load, "col", col );
	}
	FPCODE LoadDif( std::ifstream &mqoFile, std::string& load )
	{
		return LoadFloatParenthesi( load, "dif", &dif );
	}
	FPCODE LoadAmb( std::ifstream &mqoFile, std::string& load )
	{
		return LoadFloatParenthesi( load, "amb", &amb );
	}
	FPCODE LoadEmi( std::ifstream &mqoFile, std::string& load )
	{
		return LoadFloatParenthesi( load, "emi", &emi );
	}
	FPCODE LoadSpc( std::ifstream &mqoFile, std::string& load )
	{
		return LoadFloatParenthesi( load, "spc", &spc );
	}
	FPCODE LoadPower( std::ifstream &mqoFile, std::string& load )
	{
		return LoadFloatParenthesi( load, "power", &power );
	}
	FPCODE LoadReflect( std::ifstream &mqoFile, std::string& load )
	{
		return LoadFloatParenthesi( load, "reflect", &reflect );
	}
	FPCODE LoadRefract( std::ifstream &mqoFile, std::string& load )
	{
		return LoadFloatParenthesi( load, "refract", &refract );
	}
	FPCODE LoadTex( std::ifstream &mqoFile, std::string& load )
	{
		return LoadStringParenthesi( load, "tex", &tex );
	}
	FPCODE LoadAplane( std::ifstream &mqoFile, std::string& load )
	{
		return LoadStringParenthesi( load, "aplane", &aplane );
	}
	FPCODE LoadBump( std::ifstream &mqoFile, std::string& load )
	{
		return LoadStringParenthesi( load, "bump", &bump );
	}
	FPCODE LaodProj_pos( std::ifstream &mqoFile, std::string& load )
	{
		return LoadArrayParenthesi( mqoFile, load, "proj_pos", proj_pos );
	}
	FPCODE LaodProj_scale( std::ifstream &mqoFile, std::string& load )
	{
		return LoadArrayParenthesi( mqoFile, load, "proj_scale", proj_scale );
	}
	FPCODE Laodproj_angle( std::ifstream &mqoFile, std::string& load )
	{
		return LoadArrayParenthesi( mqoFile, load, "proj_angle", proj_angle );
	}
};

class MqoVertexList : public MqoLoadObject
{
public:
	class vertex
	{
	public:
		float pos[3];
		
		vertex()
		{
			pos[0] = pos[1] = pos[2] = 0;
		}

		void Load( std::ifstream& mqoFile )
		{
			mqoFile >> pos[0];
			mqoFile >> pos[1];
			mqoFile >> pos[2];
		}
	};

	std::vector<vertex> list;

	void Load( std::ifstream &mqoFile )
	{
		unsigned int numVertex;
		mqoFile >> numVertex;
		list.resize( numVertex );

		std::string workString;
		mqoFile >> workString; // { ��ǂݍ���

		for( size_t i = 0; i < numVertex; i++ )
		{
			list[i].Load( mqoFile );
		}

		mqoFile >> workString; // } ��ǂݍ���
	}
};

class MqoFaceList : public MqoLoadObject
{
public:

	class Face
	{
	public:
		class Vertex
		{
		public:
			unsigned int V;        // ���_�C���f�b�N�X
			float UV[2];
			DWORD COL;             // ���_�F ABGR

			Vertex() : V(0), COL(0xFFFFFFFF)
			{
				UV[0] = UV[1] = 0;
			}
		};
		std::vector<Vertex> vertex; // ���_�C���f�b�N�X�ƒ��_���
		unsigned int M;             // �ގ��C���f�b�N�X

		Face() : M(0)
		{}

		void LoadV( std::ifstream &mqoFile, const std::string& load )
		{
			vertex[0].V = std::stoi( load.substr( 2 ) );
			for( size_t i = 1; i < vertex.size(); i++ )
			{
				mqoFile >> vertex[i].V;
			}
		};
		void LoadM( const std::string& load )
		{
			M = std::stoi( load.substr( 2 ) );
		}
		void LoadUV( std::ifstream &mqoFile, const std::string& load )
		{
			vertex[0].UV[0] = std::stof( load.substr( 3 ) );
			mqoFile >> vertex[0].UV[1];
			for( size_t i = 1; i < vertex.size(); i++ )
			{
				mqoFile >> vertex[i].UV[0];
				mqoFile >> vertex[i].UV[1];
			}
		}
		void LoadCOL( std::ifstream &mqoFile, const std::string& load )
		{
			vertex[0].COL = std::stoi( load.substr( 4 ) );
			for( size_t i = 1; i < vertex.size(); i++ )
			{
				mqoFile >> vertex[i].COL;
			}
		}
	};
	std::vector<Face> list;

	void Load( std::ifstream &mqoFile )
	{
		unsigned int numFace( 0 );
		mqoFile >> numFace;
		list.resize( numFace );

		std::string workString;
		mqoFile >> workString; // { �ǂݍ���

		for( size_t i = 0; i <= list.size(); )
		{
			mqoFile >> workString;
			if( workString == "}" )
				break;

			if( "0" <= workString && workString <= "9" )
			{
				i++;
				list[i - 1].vertex.resize( std::stoi( workString ) );
				continue;
			}

			if( i <= 0 )
				continue;

			if( workString.find( "COL" ) != std::string::npos )
			{
				list[i - 1].LoadCOL( mqoFile, workString );
			}
			else if( workString.find( "UV" ) != std::string::npos )
			{
				list[i - 1].LoadUV( mqoFile, workString );
			}
			else if( workString.find( "V" ) != std::string::npos )
			{
				list[i - 1].LoadV( mqoFile, workString );
			}
			else if( workString.find( "M" ) != std::string::npos )
			{
				list[i - 1].LoadM( workString );
			}
		}

		mqoFile >> workString; // } �ǂݍ���
	}

private:
};

class MqoObject : public MqoLoadObject
{
public:
	std::string name;     // �I�u�W�F�N�g�� 63byte�ȓ�
	float scale[3];       // �g�� XYZ
	float rotation[3];    // ��] YXZ
	float translation[3]; // �ړ� XYZ
	int visible;         // 0 : ��\��, 15 : �\��
	float color[3];       // �F   RGB 0~1

	MqoVertexList vertexList;
	MqoFaceList faceList;

	MqoObject()
	{}

	void Load( std::ifstream &mqoFile )
	{
		LoadName( mqoFile, name );

		FPCODE( MqoObject::*loadFP[] )( std::ifstream &mqoFile, std::string& load )
		{
			&MqoObject::LoadScale, &MqoObject::LoadRotation, &MqoObject::LoadtTranslation, &MqoObject::LoadtVisible, &MqoObject::LoadtColor, &MqoObject::LoadVertex, &MqoObject::LoadFace,
		};

		LoadLoop<MqoObject>( this, mqoFile, loadFP, ARRAYSIZE( loadFP ) );
	}

private:
	FPCODE LoadScale( std::ifstream &mqoFile, std::string& load )
	{
		return LoadArray( mqoFile, load, "scale", scale );
	}
	FPCODE LoadRotation( std::ifstream &mqoFile, std::string& load )
	{
		return LoadArray( mqoFile, load, "rotation", rotation );
	}
	FPCODE LoadtTranslation( std::ifstream &mqoFile, std::string& load )
	{
		return LoadArray( mqoFile, load, "translation", translation );
	}
	FPCODE LoadtVisible( std::ifstream &mqoFile, std::string& load )
	{
		if( load == "}" )
			return FPCODE::END;

		if( load != "visible" )
			return FPCODE::FAILURE;

		mqoFile >> visible;
		return FPCODE::SUCCESS;
	}
	FPCODE LoadtColor( std::ifstream &mqoFile, std::string& load )
	{
		return LoadArray( mqoFile, load, "color", color );
	}
	FPCODE LoadVertex( std::ifstream &mqoFile, std::string& load )
	{
		if( load == "}" )
			return FPCODE::END;

		if( load != "vertex" )
			return FPCODE::FAILURE;

		vertexList.Load( mqoFile );
		return FPCODE::SUCCESS;
	}
	FPCODE LoadFace( std::ifstream &mqoFile, std::string& load )
	{
		if( load == "}" )
			return FPCODE::END;

		if( load != "face" )
			return FPCODE::FAILURE;

		faceList.Load( mqoFile );
		return FPCODE::SUCCESS;
	}
};

bool tdnMesh::LoadMqo( char *filename )
{
	std::ifstream mqoFile;
	if( OpenFstream( &mqoFile, filename ) == false )
		return false;

	std::vector<MqoMaterial> materialList;
	std::vector<MqoObject> objectList;

	// �ǂݍ���ł܂Ƃ߂�
	while( true )
	{
		std::string command;
		mqoFile >> command;
		if( mqoFile.eof() )
			break;

		// �}�e���A���ǂݍ���
		if( command.find( "Material" ) != std::string::npos )
		{
			unsigned int numMaterial;
			mqoFile >> numMaterial;
			materialList.resize( numMaterial );

			for( unsigned int i = 0; i < numMaterial; i++ )
			{
				materialList[i].Load( mqoFile );
			}
		}
		// �I�u�W�F�N�g�ǂݍ���
		else if( command.find( "Object" ) != std::string::npos )
		{
			objectList.push_back( MqoObject() );
			objectList.rbegin()->Load( mqoFile );
		}
	}

	return true;
}

/********/
/* �X�V */
/********/

void tdnMesh::UpdateWorldMatrix()
{
	D3DXMatrixRotationQuaternion( &worldMatrix, &rot );
	worldMatrix._11 *= scale.x;
	worldMatrix._12 *= scale.x;
	worldMatrix._13 *= scale.x;
	worldMatrix._14 *= scale.x;
	worldMatrix._21 *= scale.y;
	worldMatrix._22 *= scale.y;
	worldMatrix._23 *= scale.y;
	worldMatrix._24 *= scale.y;
	worldMatrix._31 *= scale.z;
	worldMatrix._32 *= scale.z;
	worldMatrix._33 *= scale.z;
	worldMatrix._34 *= scale.z;
	worldMatrix._41 = pos.x;
	worldMatrix._42 = pos.y;
	worldMatrix._43 = pos.z;
	worldMatrix._44 = 1;
}

/********/
/* �`�� */
/********/

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

/*********************/
/* �Z�b�^�[ �Q�b�^�[ */
/*********************/

const Vector3& tdnMesh::Pos()
{
	return pos;
}
void tdnMesh::Pos( const Vector3& in )
{
	pos = in;
}
const Vector3& tdnMesh::Scale()
{
	return scale;
}
void tdnMesh::Scale( const Vector3& in )
{
	scale = in;
}
const Quaternion& tdnMesh::Rot()
{
	return rot;
}
void tdnMesh::Rot( const Quaternion& in )
{
	rot = in;
}
const Matrix& tdnMesh::WorldMatrix()
{
	return worldMatrix;
}
void tdnMesh::WorldMatrix( const Matrix& in )
{
	worldMatrix = in;
}
