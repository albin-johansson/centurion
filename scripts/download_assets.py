#  Copyright (C) 2019-2024 Albin Johansson (MIT License)

import argparse
import centurion
import os
import sys

PNG_FILE_URL = "https://dummyimage.com/128x96.png"
MP3_FILE_URL = "https://opengameart.org/sites/default/files/the_field_of_dreams.mp3"

WAV_ZIP_URL = "https://opengameart.org/sites/default/files/UI_SFX_Set.zip"
TTF_ZIP_URL = "https://dl.dafont.com/dl/?f=daniel"


def _download_file_if_missing(url: str, outfile: str):
    try:
        if not os.path.exists(outfile):
            centurion.download_file(url, outfile)
        else:
            print(f"'{outfile}' already exists, skipping download")
    except IOError:
        print(f"ERROR: could not download {url}")


def _download_archive_if_missing(url: str, archive_name: str, extract_dir: str):
    if not os.path.isdir(extract_dir):
        centurion.download_and_extract_archive(url, archive_name, extract_dir)
    else:
        print(f"Archive '{archive_name}' already extracted")


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--outdir", metavar="<dir>", type=str, required=True, help="The output directory")

    arguments: argparse.Namespace
    try:
        arguments = parser.parse_args()
    except argparse.ArgumentError or argparse.ArgumentTypeError:
        parser.print_help()
        sys.exit(-1)

    return arguments


def main():
    arguments = _parse_args()
    output_dir = arguments.outdir

    if not os.path.isdir(output_dir):
        print(f"Creating directory '{output_dir}'")
        os.mkdir(output_dir)

    if not os.path.isdir(".cache"):
        os.mkdir(".cache")

    png_file = ".cache/test.png"
    _download_file_if_missing(PNG_FILE_URL, png_file)

    mp3_file = ".cache/test.mp3"
    _download_file_if_missing(MP3_FILE_URL, mp3_file)

    ttf_file = ".cache/ttf/daniel.ttf"
    _download_archive_if_missing(TTF_ZIP_URL, ".cache/ttf.zip", ".cache/ttf")

    wav_file = ".cache/wav/click3.wav"
    _download_archive_if_missing(WAV_ZIP_URL, ".cache/wav.zip", ".cache/wav")

    centurion.copy_file(png_file, f"{output_dir}/test.png")
    centurion.copy_file(ttf_file, f"{output_dir}/test.ttf")
    centurion.copy_file(mp3_file, f"{output_dir}/test.mp3")
    centurion.copy_file(wav_file, f"{output_dir}/test.wav")


if __name__ == "__main__":
    main()
