
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
/* 作成 */
/********/

bool tdnMesh::CreateVertex( unsigned int numVertexes, unsigned int vertexSize, void *vertexArray )
{
	HRESULT hr( S_OK );

	// 頂点配列のサイズ計算
	unsigned int vertexesSize = vertexSize * numVertexes;
	this->numVertexes = numVertexes;

	// バッファnew
	hr = tdnSystem::GetDevice()->CreateVertexBuffer(
		vertexesSize,    // 頂点配列のバイト数
		0,               // 使用方法 D3DUSAGE
		D3DFVF_XYZ,      // ?
		D3DPOOL_MANAGED, // ?
		&vertexBuffer,   // 頂点バッファ <out>
		0 );             // ?
	if( FAILED( hr ) )
		return false;

	// バッファにコピー
	Vector3* workVertex( nullptr );
	hr = vertexBuffer->Lock( 0, 0, ( void** ) &workVertex, 0 );      // バッファロック (バファのポインター取得)
	if( FAILED( hr ) )
		return false;
	memcpy_s( workVertex, vertexesSize, vertexArray, vertexesSize ); // バッファに頂点情報をコピー
	hr = vertexBuffer->Unlock();                                     // バッファロックを解除
	if( FAILED( hr ) )
		return false;

	return true;
}
bool tdnMesh::CreateIndexes( unsigned int numIndexes, const DWORD *indexArray )
{
	HRESULT hr( S_OK );

	this->numIndexes = numIndexes;

	// インデックス配列のサイズ計算
	unsigned int indexesSize = sizeof( DWORD ) * numIndexes;
	// インデックスnew
	hr = tdnSystem::GetDevice()->CreateIndexBuffer(
		indexesSize,     // インデックス配列のバイト数
		0,               // 使用方法 D3DUSAGE
		D3DFMT_INDEX32,  // フォーマット
		D3DPOOL_MANAGED, // ?
		&indexBuffer,    // インデックスバッファ <out>
		NULL );          // ?
	if( FAILED( hr ) )
		return false;

	// バッファにコピー
	DWORD* workIndex( nullptr );
	hr = indexBuffer->Lock( 0, 0, ( void** ) &workIndex, 0 );    // バッファロック (バファのポインター取得)
	if( FAILED( hr ) )
		return false;
	memcpy_s( workIndex, indexesSize, indexArray, indexesSize ); // バッファにインデックス情報をコピー
	hr = indexBuffer->Unlock();                                  // バッファロックを解除
	if( FAILED( hr ) )
		return false;

	return true;
}
bool tdnMesh::CreateDeclaration( unsigned int declSize, D3DVERTEXELEMENT9 *decl )
{
	HRESULT hr( S_OK );

	this->declSize = declSize;
	//FVF作成
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
/* 読み込み */
/************/

template<class TYPE_FSTREAM> bool OpenFstream( TYPE_FSTREAM *out, char *filename )
{
	out->open( filename );
	if( out->fail() ) // 開けなかった
	{
		char text[256] = {};
		sprintf_s( text, "%s が開けません", filename );
		MessageBox( NULL, text, "エラー", 0 );
		return false;
	}
	return true;
}

// MQOファイル

class MqoLoadObject
{
public:
	virtual void Load( std::ifstream &mqoFile ) = 0;

protected:
	// 関数ポインタの戻り値
	enum class FPCODE : byte
	{
		FAILURE, SUCCESS, END
	};

	// "" で囲まれた文字を読み込む
	inline void LoadName(
		std::ifstream &mqoFile,
		std::string &name )
	{
		mqoFile >> name;
		name = name.substr( 1, name.size() - 2 ); // 前後の " " を消す
	}

	// type の配列を読み込む
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

	// com(float) の形の文字列を読み込みfloatを取り出す
	inline FPCODE LoadFloatParenthesi(
		std::string& load,
		const std::string com, // 変数の名前
		float* out
		)
	{
		if( load == "}" )
			return FPCODE::END;

		if( load.substr( 0, com.size() ) != com )
			return FPCODE::FAILURE;

		*out = stof( load.substr( com.size() + 1 ) ); // 数字を取り出す
		return FPCODE::SUCCESS;
	}

	// com("string") の形の文字列を読み込みstringを取り出す
	inline FPCODE LoadStringParenthesi(
		std::string& load,
		const std::string com, // 変数の名前
		std::string* out
		)
	{
		if( load == "}" )
			return FPCODE::END;

		if( load.substr( 0, com.size() ) != com )
			return FPCODE::FAILURE;

		*out = load.substr( com.size() + 2, load.size() - com.size() - 4 ); // 数字を取り出す
		return FPCODE::SUCCESS;
	}

	// com(type type ...) の形の文字列を読み込みtypeの配列を取り出す
	template<
		class type,
			size_t size
	>
	inline FPCODE LoadArrayParenthesi(
	std::ifstream& mqoFile,
	std::string& load,
	const std::string com, // 変数の名前
	type( &out )[size]
	)
		{
			if( load == "}" )
				return FPCODE::END;

			if( load.substr( 0, com.size()) != com )
				return FPCODE::FAILURE;

			out[0] = stof( load.substr( com.size() + 1 ) ); // 数字を取り出す
			for( size_t i = 1; i < size; i++ )
			{
				mqoFile >> out[i];
			}
			std::string workString;
			mqoFile >> workString; // ")" を読む
			return FPCODE::SUCCESS;
		}

	// 関数ポインターの配列を回す
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
	std::string name;    // 材質名       31byte以内
	float col[4];        // 頂点色 RGBA  0~1
	float dif;           // 拡散光       0~1
	float amb;           // 周囲光       0~1
	float emi;           // 自己照明     0~1
	float spc;           // 反射光       0~1
	float power;         // 反射光の強さ 0~100
	float reflect;       // 鏡面反射     0~1
	float refract;       // 屈折率       1~5
	std::string tex;     // 模様テクスチャ
	std::string aplane;  // 透明テクスチャ
	std::string bump;    // 凹凸テクスチャ
	float proj_pos[3];   // 位置 XYZ
	float proj_scale[3]; // 拡大率 XYZ
	float proj_angle[3]; // 角度 YXZ     -180~180

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
		mqoFile >> workString; // { を読む
		LoadName( mqoFile, name );

		// 変数を読み込む関数
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
		mqoFile >> workString; // { を読み込む

		for( size_t i = 0; i < numVertex; i++ )
		{
			list[i].Load( mqoFile );
		}

		mqoFile >> workString; // } を読み込む
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
			unsigned int V;        // 頂点インデックス
			float UV[2];
			DWORD COL;             // 頂点色 ABGR

			Vertex() : V(0), COL(0xFFFFFFFF)
			{
				UV[0] = UV[1] = 0;
			}
		};
		std::vector<Vertex> vertex; // 頂点インデックスと頂点情報
		unsigned int M;             // 材質インデックス

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
		mqoFile >> workString; // { 読み込み

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

		mqoFile >> workString; // } 読み込み
	}

private:
};

class MqoObject : public MqoLoadObject
{
public:
	std::string name;     // オブジェクト名 63byte以内
	float scale[3];       // 拡大 XYZ
	float rotation[3];    // 回転 YXZ
	float translation[3]; // 移動 XYZ
	int visible;         // 0 : 非表示, 15 : 表示
	float color[3];       // 色   RGB 0~1

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

	// 読み込んでまとめる
	while( true )
	{
		std::string command;
		mqoFile >> command;
		if( mqoFile.eof() )
			break;

		// マテリアル読み込み
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
		// オブジェクト読み込み
		else if( command.find( "Object" ) != std::string::npos )
		{
			objectList.push_back( MqoObject() );
			objectList.rbegin()->Load( mqoFile );
		}
	}

	return true;
}

/********/
/* 更新 */
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
/* 描画 */
/********/

void tdnMesh::Render( tdnShader *shader, char *technique )
{
	unsigned int numPass = shader->Begin( technique );

	shader->SetValue( "worldMatrix", worldMatrix );

	//使用ストリーム指定と頂点バッファ設定
	tdnSystem::GetDevice()->SetStreamSource( 0, vertexBuffer, 0, declSize );
	//頂点インデックス指定
	tdnSystem::GetDevice()->SetIndices( indexBuffer );
	//頂点構造体指定
	tdnSystem::GetDevice()->SetVertexDeclaration( decl );
	for( unsigned int i = 0; i < numPass; i++ )
	{
		shader->BeginPass( i );

		//描画(面二つと０から始まる頂点と指定)
		tdnSystem::GetDevice()->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0, //開始地点からの相対位置
			0, //最小インデックス番号
			numIndexes, //最大インデックス番号
			0, //インデックス配列の読み取り位置	
			numFaces //面の数
			);

		shader->EndPass();
	}

	shader->End();
}

/*********************/
/* セッター ゲッター */
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
