// 统计指定目录下所有源文件和头文件的行数
#include <tools_statistics.h>

static sys_int g_total_lines = 0;

sys_int main(sys_int argc, sys_char *argv[])
{
  if (argc != 2)
  {
    WARN("Usage: %s <directory_path>\n", argv[0]);
    return 1;
  }

  traverseDir(argv[1]);

  INFO("Total lines: %d\n", g_total_lines);

  return 0;
}

sys_void countLines(const sys_char *filename)
{
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    ERROR("Failed to open file: %s\n", filename);
    return;
  }

  sys_int lines = 0;
  while (!feof(file))
  {
    if (fgetc(file) == '\n')
    {
      lines++;
    }
  }

  INFO("%s: %d lines\n", filename, lines);

  g_total_lines += lines;

  fclose(file);
}

sys_void traverseDir(const sys_char *dirPath)
{
  DIR *dir = opendir(dirPath);
  if (!dir)
  {
    ERROR("Failed to open directory: %s\n", dirPath);
    return;
  }

  struct dirent *entry;
  sys_char path[1024];
  while ((entry = readdir(dir)) != NULL)
  {
    if (sys_strcmp(entry->d_name, ".") == 0 || sys_strcmp(entry->d_name, "..") == 0)
    {
      continue;
    }

    sys_snprintf(path, sizeof(path), "%s/%s", dirPath, entry->d_name);

    struct stat path_stat;
    stat(path, &path_stat);

    if (S_ISDIR(path_stat.st_mode))
    {
      traverseDir(path);
    }
    else
    {
      sys_char *ext = strrchr(entry->d_name, '.');
      if (ext && (sys_strcmp(ext, ".c") == 0 || sys_strcmp(ext, ".h") == 0))
      {
        countLines(path);
      }
    }
  }

  closedir(dir);
}