# las4s e pelados

This repository hosts *las4s e pelados*, UFPE’s ICPC team reference document.

The PDF generator workflow/code was adapted from the 
[KACTL repository](https://github.com/kth-competitive-programming/kactl).

## Build Instructions 

### 1. Install Latex

```bash
sudo apt-get install texlive-latex-base texlive-latex-recommended texlive-latex-extra
```

### 2. Generate pdf

```bash
make las4s
```

For a full list of available commands:
```bash
make help
```

## Adding Code

To add new snippets or modules:

- Place the .cpp file inside the appropriate directory.
- Add its entry to the directory’s chapter.tex.
- To add a new directory, edit content/las4s.tex and include the directory there.
- Every directory must contain its own chapter.tex.