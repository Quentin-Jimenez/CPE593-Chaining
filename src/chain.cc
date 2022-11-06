class Chain
{
    public:

        // Constructors for Chain, allows multiple datatypes as input
        Chain(const string&);
        Chain(const char*);
        Chain(const Rope&);
        Chain(Rope&&);
        ~Chain(void);

        // Inserts new String into Chain
        void insert(unsigned int, const char*);
        void insert(unsigned int, const string&);

        // Returns total number of strings in chain
        unsigned int length(void) const;

        // Displays current tree-structure of chain
        void print_tree(std::ostream&);

        // Copies chain into new memory pool
        void copy(char*, unsigned int) const;

        // Compresses chain into 1 string
        void consolidate(void);

    private:

        struct Node
        {
            ~Node(void);
            Node(void);
            void print_tree(std::ostream&, unsigned int);

            Node *left, *right;
            unsigned int weight;
        };

        // Data 
        Node* root;

};