#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem>

namespace MyUtility
{
	// MyUtility���O��ԃX�R�[�v�Ŗ��O���std���ȗ�����
	using namespace std;

	/// <summary>
	/// ������Ɋւ��郆�[�e�B���e�B�N���X
	/// </summary>
	class String final
	{
	public:
		/// <summary>
		/// �w�肳�ꂽ�����ŋ�؂�ꂽ������������i�[���镶����z���Ԃ��܂��B
		/// </summary>
		/// <param name="sourceString">�����Ώۂ̕�����</param>
		/// <param name="delimiter">��؂蕶��</param>
		/// <returns></returns>
		inline static vector<string> Split(const string& sourceString, const char& delimiter)
		{
			// �Ԃ�l�p�̕�����z��
			vector<string> elements;

			// ����������
			string item;

			for (const auto& character : sourceString)
			{
				// ��؂蕶�������������񂪋�łȂ��Ȃ當����z��ɕ������ǉ�����
				if (character == delimiter)
				{
					if (!item.empty())
					{
						elements.push_back(item);
					}
					item.clear();
				}
				else
				{
					item += character;
				}
			}

			// �����񖖔��̕��������񂪂���Ȃ當����z��ɒǉ�����
			if (!item.empty())
			{
				elements.push_back(item);
			}

			return elements;
		}
	private:
		// �[���I�ȐÓI�N���X�Ƃ��Ĉ������߂ɃR���X�g���N�^�[����private�ɂ���

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^�[
		/// </summary>
		String() = default;

		/// <summary>
		/// �f�t�H���g�f�X�g���N�^
		/// </summary>
		~String() = default;

		/// <summary>
		/// �R�s�[�R���X�g���N�^�[
		/// </summary>
		/// <param name="">String�^�̍��Ӓl�Q��</param>
		String(const String&) = delete;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="">String�^�̍��Ӓl�Q��</param>
		/// <returns>String�^�̍��Ӓl�Q��</returns>
		String& operator=(const String&) = delete;

		/// <summary>
		/// ���[�u�R���X�g���N�^�[
		/// </summary>
		/// <param name="">String�^�̉E�Ӓl�Q��</param>
		String(String&&) = delete;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="">String�^�̉E�Ӓl�Q��</param>
		/// <returns>String�^�̍��Ӓl�Q��</returns>
		String& operator=(String&&) = delete;
	};

	/// <summary>
	/// ���t��\���N���X
	/// </summary>
	class Date final
	{
	public:
		// �N
		const int Year;

		// ��
		const string Month;

		// ��
		const int Day;

		// �j��
		const string DayOfWeek;

		// ��
		const int Hour;

		// ��
		const int Minute;

		// �b
		const int Second;

		/// <summary>
		/// �R���X�g���N�^�[
		/// </summary>
		/// <param name="year">�N</param>
		/// <param name="month">��</param>
		/// <param name="day">��</param>
		/// <param name="dayOfWeek">�j��</param>
		/// <param name="hour">��</param>
		/// <param name="minute">��</param>
		/// <param name="second">�b</param>
		Date(const int& year, const string& month, const int& day, const string& dayOfWeek, const int& hour, const int& minute, const int& second) :
			Year(year),
			Month(month),
			Day(day),
			DayOfWeek(dayOfWeek),
			Hour(hour),
			Minute(minute),
			Second(second)
		{}

		/// <summary>
		/// �f�t�H���g�f�X�g���N�^
		/// </summary>
		~Date() = default;
	};

	/// <summary>
	/// ���t�Ɋւ��郆�[�e�B���e�B�N���X
	/// </summary>
	class DateTime final
	{
	public:
		/// <summary>
		/// ���݂̌��n������Ԃ��܂��B
		/// </summary>
		/// <returns>�����̓��t</returns>
		inline static Date Now()
		{
			// �ÓI�֐��X�R�[�v�Ŗ��O���std::chrono���ȗ�����
			using namespace std::chrono;

			// ���ݓ������擾
			auto timePoint = system_clock::now();

			// time_point��POSIX ���ԁitime_t�j�ɕϊ�
			auto timeTValue = system_clock::to_time_t(timePoint);

			// ���Ԃ�\������������o���o�b�t�@
			char buffer[26];

			// POSIX ���Ԃ��玞�Ԃ�\��������ɕϊ�
			ctime_s(buffer, sizeof buffer, &timeTValue);

			// char[]��string�ɕϊ�
			auto timeString = string(buffer);

			// �����񂩂�\n���폜����
			timeString = timeString.substr(0, timeString.size() - 1);

			// ���p�X�y�[�X����؂蕶���Ƃ��ĕ�����𕪊�����
			auto result = String::Split(timeString, ' ');

			// �j�������o��
			auto dayOfWeek = result[0];

			// �������o��
			auto month = result[1];

			// �������o��
			auto day = stoi(result[2]);

			// �N�����o��
			auto year = stoi(result[4]);

			// ���A���A�b�ɕ�������
			auto hourAndMinuteAndSecond = String::Split(result[3], ':');

			// �������o��
			auto hour = stoi(hourAndMinuteAndSecond[0]);

			// �������o��
			auto minute = stoi(hourAndMinuteAndSecond[1]);

			// �b�����o��
			auto second = stoi(hourAndMinuteAndSecond[2]);

			return Date{ year,  month,  day,  dayOfWeek,  hour,  minute,  second };
		}
	private:
		// �[���I�ȐÓI�N���X�Ƃ��Ĉ������߂ɃR���X�g���N�^�[����private�ɂ���

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^�[
		/// </summary>
		DateTime() = default;

		/// <summary>
		/// �f�t�H���g�f�X�g���N�^
		/// </summary>
		~DateTime() = default;

		/// <summary>
		/// �R�s�[�R���X�g���N�^�[
		/// </summary>
		/// <param name="">DateTime�^�̍��Ӓl�Q��</param>
		DateTime(const DateTime&) = delete;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="">DateTime�^�̍��Ӓl�Q��</param>
		/// <returns>DateTime�^�̍��Ӓl�Q��</returns>
		DateTime& operator=(const DateTime&) = delete;

		/// <summary>
		/// ���[�u�R���X�g���N�^�[
		/// </summary>
		/// <param name="">DateTime�^�̉E�Ӓl�Q��</param>
		DateTime(DateTime&&) = delete;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="">DateTime�^�̉E�Ӓl�Q��</param>
		/// <returns>DateTime�^�̍��Ӓl�Q��</returns>
		DateTime& operator=(DateTime&&) = delete;
	};

	/// <summary>
	/// �t�@�C���Ɋւ��郆�[�e�B���e�B�N���X
	/// </summary>
	class FileSystem
	{
	public:
		/// <summary>
		/// �w�肵���f�B���N�g���̃p�X�ɂ���t�@�C���A�f�B���N�g���̐���Ԃ��܂��B
		/// </summary>
		/// <param name="root"></param>
		/// <returns></returns>
		inline static size_t FileCount(const filesystem::path& path)
		{
			// �ÓI�֐��X�R�[�v�Ŗ��O���std::filesystem���ȗ�����
			using namespace std::filesystem;
			
			// �p�X�����݂��Ȃ����w�肵���p�X���f�B���N�g���łȂ��Ȃ�0��Ԃ�
			if (!exists(path) || !is_directory(path)) return 0;

			// �t�@�C���̐�
			std::size_t result = 0;
			
			// �f�B���N�g���C�e���[�^
			directory_iterator last;

			// �ċA�I�Ƀt�@�C���A�f�B���N�g���̐��𐔂���
			for (directory_iterator pos(path); pos != last; ++pos)
			{
				++result;
				if (is_directory(*pos)) result += FileCount(pos->path());
			}

			return result;
		}
	private:
		// �[���I�ȐÓI�N���X�Ƃ��Ĉ������߂ɃR���X�g���N�^�[����private�ɂ���

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^�[
		/// </summary>
		FileSystem() = default;

		/// <summary>
		/// �f�t�H���g�f�X�g���N�^
		/// </summary>
		~FileSystem() = default;

		/// <summary>
		/// �R�s�[�R���X�g���N�^�[
		/// </summary>
		/// <param name="">FileSystem�^�̍��Ӓl�Q��</param>
		FileSystem(const FileSystem&) = delete;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="">FileSystem�^�̍��Ӓl�Q��</param>
		/// <returns>FileSystem�^�̍��Ӓl�Q��</returns>
		FileSystem& operator=(const FileSystem&) = delete;

		/// <summary>
		/// ���[�u�R���X�g���N�^�[
		/// </summary>
		/// <param name="">FileSystem�^�̉E�Ӓl�Q��</param>
		FileSystem(FileSystem&&) = delete;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="">FileSystem�^�̉E�Ӓl�Q��</param>
		/// <returns>FileSystem�^�̍��Ӓl�Q��</returns>
		FileSystem& operator=(FileSystem&&) = delete;
	};

	/// <summary>
	/// ���O�Ɋւ��郆�[�e�B���e�B�N���X
	/// </summary>
	class Log final
	{
	public:
		/// <summary>
		/// ���݂̌��n���t�Ɋ�Â��ă��O�p�̃f�B���N�g�����쐬���܂��B
		/// </summary>
		/// <returns>���O�p�̃f�B���N�g���̑��΃p�X</returns>
		inline static string CreateLogDirectoryFromTodaysDate()
		{
			// �ÓI�֐��X�R�[�v�Ŗ��O���std::filesystem���ȗ�����
			using namespace std::filesystem;

			// ���݂̌��n���t���擾����
			auto date = DateTime::Now();

			// Log�f�B���N�g���̑��΃p�X
			auto logDirectory = "Log"s;

			// ����Log�f�B���N�g�������݂��Ȃ��Ȃ�Log�f�B���N�g�������
			if (!exists(logDirectory))
			{
				create_directory(logDirectory);
			}

			// year�f�B���N�g���̑��΃p�X
			auto yearDirectory = "Log"s + "/"s + to_string(date.Year);

			// ����year�f�B���N�g�������݂��Ȃ��Ȃ�year�f�B���N�g�������
			if (!exists(yearDirectory))
			{
				create_directory(yearDirectory);
			}

			// month�f�B���N�g���̑��΃p�X
			auto monthDirectory = "Log"s + "/"s + to_string(date.Year) + "/"s + date.Month;

			// ����month�f�B���N�g�������݂��Ȃ��Ȃ�month�f�B���N�g�������
			if (!exists(monthDirectory))
			{
				create_directory(monthDirectory);
			}

			// day�f�B���N�g���̑��΃p�X
			auto dayDirectory = "Log"s + "/"s + to_string(date.Year) + "/"s + date.Month + "/"s + to_string(date.Day);

			// ����day�f�B���N�g�������݂��Ȃ��Ȃ�day�f�B���N�g�������
			if (!exists(dayDirectory))
			{
				create_directory(dayDirectory);
			}

			// day�f�B���N�g�����̃t�@�C���̐����擾����
			auto fileCount = FileSystem::FileCount(dayDirectory);

			// �X�g�����O�X�g���[��
			std::stringstream stringStream;

			// ������𔼊p5�����ɂ��낦��A5���������ꍇ��0�Ŗ��߂�
			stringStream << setw(5) << setfill('0') << to_string(fileCount + 1);

			// ���O��day�f�B���N�g�����̃t�@�C�����̃f�B���N�g���̑��΃p�X
			auto fileCountDirectory = "Log"s + "/"s + to_string(date.Year) + "/"s + date.Month + "/"s + to_string(date.Day) + "/"s + stringStream.str();

			// ���O��day�f�B���N�g�����̃t�@�C�����̃f�B���N�g�������
			create_directory(fileCountDirectory);

			return fileCountDirectory;
		}
	private:
		// �[���I�ȐÓI�N���X�Ƃ��Ĉ������߂ɃR���X�g���N�^�[����private�ɂ���

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^�[
		/// </summary>
		Log() = default;

		/// <summary>
		/// �f�t�H���g�f�X�g���N�^
		/// </summary>
		~Log() = default;

		/// <summary>
		/// �R�s�[�R���X�g���N�^�[
		/// </summary>
		/// <param name="">Log�^�̍��Ӓl�Q��</param>
		Log(const Log&) = delete;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="">Log�^�̍��Ӓl�Q��</param>
		/// <returns>Log�^�̍��Ӓl�Q��</returns>
		Log& operator=(const Log&) = delete;

		/// <summary>
		/// ���[�u�R���X�g���N�^�[
		/// </summary>
		/// <param name="">Log�^�̉E�Ӓl�Q��</param>
		Log(Log&&) = delete;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="">Log�^�̉E�Ӓl�Q��</param>
		/// <returns>Log�^�̍��Ӓl�Q��</returns>
		Log& operator=(Log&&) = delete;
	};
}