import os


def patch_version_line(line, version):
    opening_tag = "<version>"
    closing_tag = "</version>"
    idx = line.find(opening_tag)
    if idx == -1:
        return line
    line_begin = line[:idx + len(opening_tag)]
    line_end = line[line.find(closing_tag):]
    return line_begin + version + line_end

def main():
    version = os.getenv("APPVEYOR_BUILD_VERSION")
    nuspec_path = os.path.join('nuget', 'matplotlib-cpp.nuspec')
    with open(nuspec_path) as nuspec:
        content = nuspec.readlines()
    with open(nuspec_path, 'w') as nuspec:
        nuspec.writelines(patch_version_line(line, version) for line in content)


if __name__ == "__main__":
    main()
