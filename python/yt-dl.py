import subprocess
url = input("input url >:")
a = input("webm(1) or mp4(2) >:")
webm = [
    "yt-dlp",
    "-f", "bv+ba",
    "--merge-output-format", "webm",
    url
]
mp4 = [
    "yt-dlp",
    "-f", "bv+ba",
    "--merge-output-format", "webm",
    url
]
if a == "1":
    subprocess.run(webm)
elif a == "2":
    subprocess.run(mp4)