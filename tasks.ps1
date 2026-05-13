param(
    [string]$Task = "help"
)

$FILES_CPP = git ls-files "src/*.cpp"
$FILES_H = git ls-files "src/*.h"

switch ($Task)
{
    "check" {
        clang-format --dry-run --Werror $FILES_CPP $FILES_H

        clang-tidy `
            -p cmake-build-minsizerel-visual-studio2019 `
            --use-color `
            $FILES_CPP
    }

    "fix" {
        clang-format -i $FILES_CPP $FILES_H

        clang-tidy `
            -p cmake-build-minsizerel-visual-studio2019 `
            --use-color `
            --fix `
            --fix-errors `
            $FILES_CPP `
    }

    default {
        Write-Host ""
        Write-Host "Available targets:"
        Write-Host "  check      Run clang-tidy + clang-format in dry-run mode"
        Write-Host "  fix        Run clang-format in fix mode"
        Write-Host ""
    }
}
