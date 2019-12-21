cleanups = 0
nbr = 0
acc = 0
last = 0
cnt = 0

npushes = gets.to_i

pushes = gets.split.map(&:to_i)
begin
  push = pushes[cnt]
  if (push-last)*nbr + acc > 19
    cleanups += 1
    acc = 0
    nbr = 1
  else
    acc = acc + (push-last)* nbr
    nbr = nbr + 1
  end
  last = push
  cnt += 1
end while cnt < npushes

puts cleanups + 1
