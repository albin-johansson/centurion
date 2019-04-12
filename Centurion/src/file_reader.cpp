#include "file_reader.h"
#include <stdio.h>

namespace centurion {
namespace io {

FileReader::FileReader() { file = nullptr; }

FileReader::~FileReader() {}

void FileReader::ReadFile(const std::string path) {
  file = std::make_unique<File>(path);
  // Close();
  // file = SDL_RWFromFile(path.c_str(), "r+b");  // TODO What does "r+b" mean?
  // if (file == nullptr) {
  //  printf("Failed to open file! Error: %s\n", SDL_GetError());
  //  isOpen = false;
  //} else {
  //  isOpen = true;
  //}
}

// void FileReader::Close() {
//  if (file != nullptr) {
//    SDL_RWclose(file);
//  }
//}

}  // namespace io
}  // namespace centurion

/*
bool loadMedia() {
  // Text rendering color
  SDL_Color textColor = {0, 0, 0, 0xFF};
  SDL_Color highlightColor = {0xFF, 0, 0, 0xFF};

  // Loading success flag
  bool success = true;

  // Open the font
  gFont = TTF_OpenFont("33_file_reading_and_writing/lazy.ttf", 28);
  if (gFont == NULL) {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  } else {
    // Render the prompt
    if (!gPromptTextTexture.loadFromRenderedText("Enter Data:", textColor)) {
      printf("Failed to render prompt text!\n");
      success = false;
    }
  }

  // Open file for reading in binary
  SDL_RWops* file =
      SDL_RWFromFile("33_file_reading_and_writing/nums.bin", "r+b");

  // File does not exist
  if (file == NULL) {
    printf("Warning: Unable to open file! SDL Error: %s\n", SDL_GetError());

    // Create file for writing
    file = SDL_RWFromFile("33_file_reading_and_writing/nums.bin", "w+b");
    if (file != NULL) {
      printf("New file created!\n");

      // Initialize data
      for (int i = 0; i < TOTAL_DATA; ++i) {
        gData[i] = 0;
        SDL_RWwrite(file, &gData[i], sizeof(Sint32), 1);
      }

      // Close file handler
      SDL_RWclose(file);
    } else {
      printf("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
  }
  // File exists
  else {
    // Load data
    printf("Reading file...!\n");
    for (int i = 0; i < TOTAL_DATA; ++i) {
      SDL_RWread(file, &gData[i], sizeof(Sint32), 1);
    }

    // Close file handler
    SDL_RWclose(file);
  }

  // Initialize data textures
  gDataTextures[0].loadFromRenderedText(std::to_string(gData[0]),
                                        highlightColor);
  for (int i = 1; i < TOTAL_DATA; ++i) {
    gDataTextures[i].loadFromRenderedText(std::to_string(gData[i]), textColor);
  }

  return success;
}

void close() {
  // Open data for writing
  SDL_RWops* file =
      SDL_RWFromFile("33_file_reading_and_writing/nums.bin", "w+b");
  if (file != NULL) {
    // Save data
    for (int i = 0; i < TOTAL_DATA; ++i) {
      SDL_RWwrite(file, &gData[i], sizeof(Sint32), 1);
    }

    // Close file handler
    SDL_RWclose(file);
  } else {
    printf("Error: Unable to save file! %s\n", SDL_GetError());
  }

  // Free loaded images
  gPromptTextTexture.free();
  for (int i = 0; i < TOTAL_DATA; ++i) {
    gDataTextures[i].free();
  }

  // Free global font
  TTF_CloseFont(gFont);
  gFont = NULL;

  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
*/