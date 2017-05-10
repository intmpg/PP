
class CBatcherSort
{
public:
	size_t GetSize();
	size_t GetThreads();
	std::vector<int> SortProcess(std::vector<int> & vec);
	std::vector<int> FillArray(size_t size);

private:
	void MergeTapes(std::vector<int> & v1, std::vector<int> & v2);
	std::vector<int> ComposeTape(std::vector<int> tape1, std::vector<int> tape2);

protected:
	size_t size;
	size_t threads;
};
