import os
import re
from datetime import datetime

import pytz

RESULT_FILE = "docs/public/result.txt"
STATUS_FILE = "docs/public/status.txt"

# ファイルから値を取得
with open(STATUS_FILE, encoding="utf-8") as f:
    STATUS = f.read().strip()

# 日付を取得
tz = pytz.timezone("Asia/Tokyo")
DATE = datetime.now(tz).strftime("%Y-%m-%d %H:%M %Z")
print(f"[update_pages.py] STATUS={STATUS} DATE={DATE}")

# docs/index.md の書き換え
with open("docs/index.md", encoding="utf-8") as f:
    content = f.read()

content = re.sub(r"text: \[.*\]", f"text: [{STATUS}]", content)
content = re.sub(r"tagline: .* 更新", f"tagline: {DATE} 更新", content)

with open("docs/index.md", "w", encoding="utf-8") as f:
    f.write(content)

# GITHUB_OUTPUT への出力
with open(os.environ["GITHUB_OUTPUT"], "a", encoding="utf-8") as f:
    f.write(f"status={STATUS}\n")
    f.write(f"date={DATE}\n")
