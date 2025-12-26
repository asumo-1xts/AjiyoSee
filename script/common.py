"""共通関数モジュール"""

from datetime import date, datetime, timedelta, timezone


def write_txt(content: str, path: str):
    """結果コードを指定したファイルに書き込む"""
    with open(path, "w", encoding="utf-8") as f:
        f.write(str(content))
    print(f"[common.py] {path}を更新: {content}")


def read_result(path: str = "result.txt") -> int:
    """result.txt を読み取って int を返す"""
    try:
        with open(path, encoding="utf-8") as f:
            return int(f.read().strip())
    except Exception:
        return 3  # UNKNOWN


def utc_to_jst(dt_utc_str: str) -> datetime:
    """X API の UTC 文字列を JST datetime に変換"""
    dt_utc = datetime.strptime(dt_utc_str, "%Y-%m-%dT%H:%M:%S.%fZ").replace(
        tzinfo=timezone.utc
    )
    return dt_utc.astimezone(timezone(timedelta(hours=9)))


def today_jst() -> date:
    """今日の日付（JST）を返す"""
    return (
        datetime.now(timezone.utc)
        .astimezone(timezone(timedelta(hours=9)))
        .date()
    )
