#  Copyright (C) 2019-2024 Albin Johansson (MIT License)

import os
import shutil
import urllib.request


def copy_file(src: str, dst: str):
    if os.path.isfile(src):
        print(f"Copying {src} to {dst}")
        shutil.copy(src, dst)
    else:
        print(f"ERROR: could not copy missing file {src}")


def download_file(url: str, outfile: str):
    print(f"Downloading {url} to {outfile}")

    opener = urllib.request.build_opener()
    opener.addheaders = [("User-agent", "Mozilla/5.0")]

    urllib.request.install_opener(opener)
    urllib.request.urlretrieve(url, outfile)


def download_and_extract_archive(url: str, archive_name: str, extract_dir: str):
    download_file(url, archive_name)

    print(f"Extracting {archive_name} to {extract_dir}")
    shutil.unpack_archive(archive_name, extract_dir)
