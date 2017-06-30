# MURO summer 2017 ~

## Make github account

Email aaron: aam021@eng.ucsd.edu with account user name

## get github repository

go to catkin workspace:

`cd ~/catkin_ws/src`

clone github repository:

```
git clone https://github.com/aaronma37/muro_summer_2017.git

cd /muro_summer_2017

git fetch (enter username and password)
```

create branch:

```
git checkout --orphan (YOUR_NAME)_branch
git commit -a -m "Initial Commit"
git push origin (YOUR_NAME)_branch
```

At this point you should be on your branch. you can check with

`git branch`

which will return all branches and with a `*` on the current one.

## Create catkin_package

. . . . .

When you are done with work for the day, update the repository

```
cd ~/catkin_ws/src/muro_summer_2017

git add .

git commit -m "update message"

git push origin (YOUR_NAME)_branch
```
