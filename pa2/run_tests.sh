echo 'running tests'

for i in {1..3};
do
	./prog2 < test_cases/test$i.txt | diff answers_test_cases/answers_test$i.txt -
done

./prog2 < test_cases/test_notinserted.txt | diff answers_test_cases/answers_test_notinserted.txt -
echo 'done'
