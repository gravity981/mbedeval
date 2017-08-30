# Git Basics :fire:
Command | Meaning
--- | ---
git init | init git repo
git add remote <name> <url> | add remote repo
git add . | add all modified files to staging area
git commit -m "message" | commit files in staging area with commit-message
git commit --amend | are neat
git push --set-upstream origin master | bla
git checkout -b <branch> | checkout new (-b) branch
git pull --rebase | pull branch and rebase local commits on top

# Merging
:warning: Take care when discarding changes

# Bisect
* Binary Search Commit
* ``git bisect start`` start bisect
* ``git bisect bad`` mark commit as bad
* ``git bisect good <commit>`` mark commit as good
* a binary search algorithm checks out a commit between good and bad
* build and test software
* if working, then enter ``git bisect good``, else enter ``git bisect bad``
* the binary search algorithm checks out next commit
* repeat steps above
* bisect will end as soon as enough revisions have been tested. It will point to the commit that introduced a bug to your software
* ``git bisect reset [commit]`` will exit bisect state and restore data, optionally you can reset to  a specific commit

# Other
* Write commit messages in present tense using the imperative mood
* Show Commit Log ``git log --pretty=%P -n <nr> <commit>``
