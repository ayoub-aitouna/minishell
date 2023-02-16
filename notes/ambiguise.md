# ambiguise

bash$ export $a="ls -la"
bash$ >$a
bash$ $a: ambiguous redirect


bash$ export $a="ls"
bash$ >$a_
bash$ $a: ambiguous redirect