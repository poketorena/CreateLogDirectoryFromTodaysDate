#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem>

namespace MyUtility
{
    // MyUtility名前空間スコープで名前空間stdを省略する
    using namespace std;

    /// <summary>
    /// 文字列に関するユーティリティクラス
    /// </summary>
    class String final
    {
    public:
        /// <summary>
        /// 指定された文字で区切られた部分文字列を格納する文字列配列を返します。
        /// </summary>
        /// <param name="sourceString">処理対象の文字列</param>
        /// <param name="delimiter">区切り文字</param>
        /// <returns></returns>
        inline static vector<string> Split(const string& sourceString, const char& delimiter)
        {
            // 返り値用の文字列配列
            vector<string> elements;

            // 部分文字列
            string item;

            for (const auto& character : sourceString)
            {
                // 区切り文字かつ部分文字列が空でないなら文字列配列に文字列を追加する
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

            // 文字列末尾の部分文字列があるなら文字列配列に追加する
            if (!item.empty())
            {
                elements.push_back(item);
            }

            return elements;
        }
    private:
        // 擬似的な静的クラスとして扱うためにコンストラクター等をprivateにする

        /// <summary>
        /// デフォルトコンストラクターを削除
        /// </summary>
        String() = default;

        /// <summary>
        /// デフォルトデストラクターを削除
        /// </summary>
        ~String() = default;

        /// <summary>
        /// コピーコンストラクターを削除
        /// </summary>
        /// <param name="">String型の左辺値参照</param>
        String(const String&) = delete;

        /// <summary>
        /// コピー代入演算子を削除
        /// </summary>
        /// <param name="">String型の左辺値参照</param>
        /// <returns>String型の左辺値参照</returns>
        String& operator=(const String&) = delete;

        /// <summary>
        /// ムーブコンストラクターを削除
        /// </summary>
        /// <param name="">String型の右辺値参照</param>
        String(String&&) = delete;

        /// <summary>
        /// ムーブ代入演算子を削除
        /// </summary>
        /// <param name="">String型の右辺値参照</param>
        /// <returns>String型の左辺値参照</returns>
        String& operator=(String&&) = delete;
    };

    /// <summary>
    /// 日付を表すクラス
    /// </summary>
    class Date final
    {
    public:
        // 年
        const int Year;

        // 月
        const string Month;

        // 日
        const int Day;

        // 曜日
        const string DayOfWeek;

        // 時
        const int Hour;

        // 分
        const int Minute;

        // 秒
        const int Second;

        /// <summary>
        /// コンストラクター
        /// </summary>
        /// <param name="year">年</param>
        /// <param name="month">月</param>
        /// <param name="day">日</param>
        /// <param name="dayOfWeek">曜日</param>
        /// <param name="hour">時</param>
        /// <param name="minute">分</param>
        /// <param name="second">秒</param>
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
        /// デフォルトデストラクターを削除
        /// </summary>
        ~Date() = default;
    };

    /// <summary>
    /// 日付に関するユーティリティクラス
    /// </summary>
    class DateTime final
    {
    public:
        /// <summary>
        /// 現在の現地日時を返します。
        /// </summary>
        /// <returns>今日の日付</returns>
        inline static Date Now()
        {
            // 静的関数スコープで名前空間std::chronoを省略する
            using namespace std::chrono;

            // 現在日時を取得
            auto timePoint = system_clock::now();

            // time_pointをPOSIX 時間（time_t）に変換
            auto timeTValue = system_clock::to_time_t(timePoint);

            // 時間を表す文字列を取り出すバッファ
            char buffer[26];

            // POSIX 時間から時間を表す文字列に変換
            ctime_s(buffer, sizeof buffer, &timeTValue);

            // char[]をstringに変換
            auto timeString = string(buffer);

            // 文字列から\nを削除する
            timeString = timeString.substr(0, timeString.size() - 1);

            // 半角スペースを区切り文字として文字列を分割する
            auto result = String::Split(timeString, ' ');

            // 曜日を取り出す
            auto dayOfWeek = result[0];

            // 月を取り出す
            auto month = result[1];

            // 日を取り出す
            auto day = stoi(result[2]);

            // 年を取り出す
            auto year = stoi(result[4]);

            // 時、分、秒に分解する
            auto hourAndMinuteAndSecond = String::Split(result[3], ':');

            // 時を取り出す
            auto hour = stoi(hourAndMinuteAndSecond[0]);

            // 分を取り出す
            auto minute = stoi(hourAndMinuteAndSecond[1]);

            // 秒を取り出す
            auto second = stoi(hourAndMinuteAndSecond[2]);

            return Date{ year,  month,  day,  dayOfWeek,  hour,  minute,  second };
        }
    private:
        // 擬似的な静的クラスとして扱うためにコンストラクター等をprivateにする

        /// <summary>
        /// デフォルトコンストラクターを削除
        /// </summary>
        DateTime() = default;

        /// <summary>
        /// デフォルトデストラクターを削除
        /// </summary>
        ~DateTime() = default;

        /// <summary>
        /// コピーコンストラクターを削除
        /// </summary>
        /// <param name="">DateTime型の左辺値参照</param>
        DateTime(const DateTime&) = delete;

        /// <summary>
        /// コピー代入演算子を削除
        /// </summary>
        /// <param name="">DateTime型の左辺値参照</param>
        /// <returns>DateTime型の左辺値参照</returns>
        DateTime& operator=(const DateTime&) = delete;

        /// <summary>
        /// ムーブコンストラクターを削除
        /// </summary>
        /// <param name="">DateTime型の右辺値参照</param>
        DateTime(DateTime&&) = delete;

        /// <summary>
        /// ムーブ代入演算子を削除
        /// </summary>
        /// <param name="">DateTime型の右辺値参照</param>
        /// <returns>DateTime型の左辺値参照</returns>
        DateTime& operator=(DateTime&&) = delete;
    };

    /// <summary>
    /// ファイルに関するユーティリティクラス
    /// </summary>
    class FileSystem
    {
    public:
        /// <summary>
        /// 指定したディレクトリのパスにあるファイル、ディレクトリの数を返します。
        /// </summary>
        /// <param name="root"></param>
        /// <returns></returns>
        inline static size_t FileCount(const filesystem::path& path)
        {
            // 静的関数スコープで名前空間std::filesystemを省略する
            using namespace std::filesystem;

            // パスが存在しないか指定したパスがディレクトリでないなら0を返す
            if (!exists(path) || !is_directory(path)) return 0;

            // ファイルの数
            std::size_t result = 0;

            // ディレクトリイテレータ
            directory_iterator last;

            // 再帰的にファイル、ディレクトリの数を数える
            for (directory_iterator pos(path); pos != last; ++pos)
            {
                ++result;
                if (is_directory(*pos)) result += FileCount(pos->path());
            }

            return result;
        }
    private:
        // 擬似的な静的クラスとして扱うためにコンストラクター等をprivateにする

        /// <summary>
        /// デフォルトコンストラクターを削除
        /// </summary>
        FileSystem() = default;

        /// <summary>
        /// デフォルトデストラクターを削除
        /// </summary>
        ~FileSystem() = default;

        /// <summary>
        /// コピーコンストラクターを削除
        /// </summary>
        /// <param name="">FileSystem型の左辺値参照</param>
        FileSystem(const FileSystem&) = delete;

        /// <summary>
        /// コピー代入演算子を削除
        /// </summary>
        /// <param name="">FileSystem型の左辺値参照</param>
        /// <returns>FileSystem型の左辺値参照</returns>
        FileSystem& operator=(const FileSystem&) = delete;

        /// <summary>
        /// ムーブコンストラクターを削除
        /// </summary>
        /// <param name="">FileSystem型の右辺値参照</param>
        FileSystem(FileSystem&&) = delete;

        /// <summary>
        /// ムーブ代入演算子を削除
        /// </summary>
        /// <param name="">FileSystem型の右辺値参照</param>
        /// <returns>FileSystem型の左辺値参照</returns>
        FileSystem& operator=(FileSystem&&) = delete;
    };

    /// <summary>
    /// ログに関するユーティリティクラス
    /// </summary>
    class Log final
    {
    public:
        /// <summary>
        /// 現在の現地日付に基づいてログ用のディレクトリを作成します。
        /// </summary>
        /// <returns>ログ用のディレクトリの相対パス</returns>
        inline static string CreateLogDirectoryFromTodaysDate()
        {
            // 静的関数スコープで名前空間std::filesystemを省略する
            using namespace std::filesystem;

            // 現在の現地日付を取得する
            auto date = DateTime::Now();

            // Logディレクトリの相対パス
            auto logDirectory = "Log"s;

            // もしLogディレクトリが存在しないならLogディレクトリを作る
            if (!exists(logDirectory))
            {
                create_directory(logDirectory);
            }

            // yearディレクトリの相対パス
            auto yearDirectory = "Log"s + "/"s + to_string(date.Year);

            // もしyearディレクトリが存在しないならyearディレクトリを作る
            if (!exists(yearDirectory))
            {
                create_directory(yearDirectory);
            }

            // monthディレクトリの相対パス
            auto monthDirectory = "Log"s + "/"s + to_string(date.Year) + "/"s + date.Month;

            // もしmonthディレクトリが存在しないならmonthディレクトリを作る
            if (!exists(monthDirectory))
            {
                create_directory(monthDirectory);
            }

            // dayディレクトリの相対パス
            auto dayDirectory = "Log"s + "/"s + to_string(date.Year) + "/"s + date.Month + "/"s + to_string(date.Day);

            // もしdayディレクトリが存在しないならdayディレクトリを作る
            if (!exists(dayDirectory))
            {
                create_directory(dayDirectory);
            }

            // dayディレクトリ内のファイルの数を取得する
            auto fileCount = FileSystem::FileCount(dayDirectory);

            // ストリングストリーム
            std::stringstream stringStream;

            // 文字列を半角5文字にそろえる、5文字無い場合は0で埋める
            stringStream << setw(5) << setfill('0') << to_string(fileCount + 1);

            // 名前がdayディレクトリ内のファイル数のディレクトリの相対パス
            auto fileCountDirectory = "Log"s + "/"s + to_string(date.Year) + "/"s + date.Month + "/"s + to_string(date.Day) + "/"s + stringStream.str();

            // 名前がdayディレクトリ内のファイル数のディレクトリを作る
            create_directory(fileCountDirectory);

            return fileCountDirectory;
        }
    private:
        // 擬似的な静的クラスとして扱うためにコンストラクター等をprivateにする

        /// <summary>
        /// デフォルトコンストラクターを削除
        /// </summary>
        Log() = default;

        /// <summary>
        /// デフォルトデストラクターを削除
        /// </summary>
        ~Log() = default;

        /// <summary>
        /// コピーコンストラクターを削除
        /// </summary>
        /// <param name="">Log型の左辺値参照</param>
        Log(const Log&) = delete;

        /// <summary>
        /// コピー代入演算子を削除
        /// </summary>
        /// <param name="">Log型の左辺値参照</param>
        /// <returns>Log型の左辺値参照</returns>
        Log& operator=(const Log&) = delete;

        /// <summary>
        /// ムーブコンストラクターを削除
        /// </summary>
        /// <param name="">Log型の右辺値参照</param>
        Log(Log&&) = delete;

        /// <summary>
        /// ムーブ代入演算子を削除
        /// </summary>
        /// <param name="">Log型の右辺値参照</param>
        /// <returns>Log型の左辺値参照</returns>
        Log& operator=(Log&&) = delete;
    };
}
