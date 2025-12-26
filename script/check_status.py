"""
check_openclose.py
filter_posts.pyの結果から営業状況を判定し、テキストファイルを更新。
"""

import csv

from common import (
    write_txt,
)

INPUT_FILE = "docs/posts_filtered.csv"
RESULT_FILE = "docs/result.txt"
STATUS_FILE = "docs/status.txt"


def main():
    result = 3  # デフォルト値をUNKNOWNに設定しておく
    try:
        with open(
            INPUT_FILE,
            encoding="utf-8",
        ) as f:
            reader = list(csv.reader(f))
            if len(reader) == 1:  # ヘッダーしか無い場合
                print("[check_status.py] 今日はポストがありません。")
                result = 1  # お休みとみなす
            else:
                header = reader[0]
                text_idx = header.index("text")
                for row in reader[1:]:  # 新しい順に走査
                    text = row[text_idx]
                    if "メニュー" in text or "オープン" in text:
                        result = 0
                        break
                    elif "お休み" in text:
                        result = 1
                        break
                    elif "完売" in text:
                        result = 2
                        break
                    else:
                        result = 3  # UNKNOWN
                        continue
    except Exception as e:
        print(f"[check_status.py] {INPUT_FILE}が見つかりません")
        print(e)
        result = 4  # X API ERROR

    write_txt(
        str(result),
        RESULT_FILE,
    )

    status_text = {
        0: "⭕ OPEN",
        1: "❌ CLOSE",
        2: "🚫 SOLD OUT",
        3: "❓ UNKNOWN",
        4: "⚠️ X-API ERROR",
    }
    write_txt(
        status_text.get(result, "❓ UNKNOWN"),
        STATUS_FILE,
    )


if __name__ == "__main__":
    main()
