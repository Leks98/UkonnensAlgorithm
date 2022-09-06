//import java.util.Arrays;
//import java.util.HashMap;
//import java.util.Map;
//
//public class ST {
//
//    public class Node {
//        private final int id;
//        private final Map<Character, Edge> edges;
//        private Node slink;
//
//        public Node(final int id) {
//            this.id = id;
//            this.edges = new HashMap<>();
//        }
//
//        public void setSlink(final Node slink) {
//            this.slink = slink;
//        }
//
//        public Map<Character, Edge> getEdges() {
//            return this.edges;
//        }
//
//        public Node getSlink() {
//            return this.slink;
//        }
//
//        public String toString(final String word) {
//            return new StringBuilder()
//                .append("{")
//                .append("\"id\"")
//                .append(":")
//                .append(this.id)
//                .append(",")
//                .append("\"slink\"")
//                .append(":")
//                .append(this.slink != null ? this.slink.id : null)
//                .append(",")
//                .append("\"edges\"")
//                .append(":")
//                .append(edgesToString(word))
//                .append("}")
//                .toString();
//        }
//
//        private StringBuilder edgesToString(final String word) {
//            final StringBuilder edgesStringBuilder = new StringBuilder();
//            edgesStringBuilder.append("{");
//            for (final Map.Entry<Character, Edge> entry : this.edges.entrySet()) {
//                edgesStringBuilder.append("\"")
//                    .append(entry.getKey())
//                    .append("\"")
//                    .append(":")
//                    .append(entry.getValue().toString(word))
//                    .append(",");
//            }
//            if (!this.edges.isEmpty()) {
//                edgesStringBuilder.deleteCharAt(edgesStringBuilder.length() - 1);
//            }
//            edgesStringBuilder.append("}");
//            return edgesStringBuilder;
//        }
//
//        public boolean contains(final String word, final String suffix) {
//            return !suffix.isEmpty()
//                && this.edges.containsKey(suffix.charAt(0))
//                && this.edges.get(suffix.charAt(0)).contains(word, suffix);
//        }
//    }
//
//    public class Edge {
//        private final int from;
//        private final int to;
//        private final Node next;
//
//        public Edge(final int from, final int to, final Node next) {
//            this.from = from;
//            this.to = to;
//            this.next = next;
//        }
//
//        public int getFrom() {
//            return this.from;
//        }
//
//        public int getTo() {
//            return this.to;
//        }
//
//        public Node getNext() {
//            return this.next;
//        }
//
//        public int getLength() {
//            return this.to - this.from;
//        }
//
//        public String toString(final String word) {
//            return new StringBuilder()
//                .append("{")
//                .append("\"content\"")
//                .append(":")
//                .append("\"")
//                .append(word.substring(this.from, this.to))
//                .append("\"")
//                .append(",")
//                .append("\"next\"")
//                .append(":")
//                .append(this.next != null ? this.next.toString(word) : null)
//                .append("}")
//                .toString();
//        }
//
//        public boolean contains(final String word, final String suffix) {
//            if (this.next == null) {
//                return word.substring(this.from, this.to).equals(suffix);
//            }
//            return suffix.startsWith(word.substring(this.from,
//                this.to)) && this.next.contains(word, suffix.substring(this.to - this.from));
//        }
//    }
//
//    public class ActivePoint {
//        private final Node activeNode;
//        private final Character activeEdgeFirstCharacter;
//        private final int activeLength;
//
//        public ActivePoint(final Node activeNode,
//            final Character activeEdgeFirstCharacter,
//            final int activeLength) {
//            this.activeNode = activeNode;
//            this.activeEdgeFirstCharacter = activeEdgeFirstCharacter;
//            this.activeLength = activeLength;
//        }
//
//        private Edge getActiveEdge() {
//            return this.activeNode.getEdges().get(this.activeEdgeFirstCharacter);
//        }
//
//        public boolean pointsToActiveNode() {
//            return this.activeLength == 0;
//        }
//
//        public boolean activeNodeIs(final Node node) {
//            return this.activeNode == node;
//        }
//
//        public boolean activeNodeHasEdgeStartingWith(final char character) {
//            return this.activeNode.getEdges().containsKey(character);
//        }
//
//        public boolean activeNodeHasSlink() {
//            return this.activeNode.getSlink() != null;
//        }
//
//        public boolean pointsToOnActiveEdge(final String word, final char character) {
//            return word.charAt(this.getActiveEdge().getFrom() + this.activeLength) == character;
//        }
//
//        public boolean pointsToTheEndOfActiveEdge() {
//            return this.getActiveEdge().getLength() == this.activeLength;
//        }
//
//        public boolean pointsAfterTheEndOfActiveEdge() {
//            return this.getActiveEdge().getLength() < this.activeLength;
//        }
//
//        public ActivePoint moveToEdgeStartingWithAndByOne(final char character) {
//            return new ActivePoint(this.activeNode, character, 1);
//        }
//
//        public ActivePoint moveToNextNodeOfActiveEdge() {
//            return new ActivePoint(this.getActiveEdge().getNext(), null, 0);
//        }
//
//        public ActivePoint moveToSlink() {
//            return new ActivePoint(this.activeNode.getSlink(),
//                this.activeEdgeFirstCharacter,
//                this.activeLength);
//        }
//
//        public ActivePoint moveTo(final Node node) {
//            return new ActivePoint(node, this.activeEdgeFirstCharacter, this.activeLength);
//        }
//
//        public ActivePoint moveByOneCharacter() {
//            return new ActivePoint(this.activeNode,
//                this.activeEdgeFirstCharacter,
//                this.activeLength + 1);
//        }
//
//        public ActivePoint moveToEdgeStartingWithAndByActiveLengthMinusOne(final Node node,
//            final char character) {
//            return new ActivePoint(node, character, this.activeLength - 1);
//        }
//
//        public ActivePoint moveToNextNodeOfActiveEdge(final String word, final int index) {
//            return new ActivePoint(this.getActiveEdge().getNext(),
//                word.charAt(index - this.activeLength + this.getActiveEdge().getLength()),
//                this.activeLength - this.getActiveEdge().getLength());
//        }
//
//        public void addEdgeToActiveNode(final char character, final Edge edge) {
//            this.activeNode.getEdges().put(character, edge);
//        }
//
//        public void splitActiveEdge(final String word,
//            final Node nodeToAdd,
//            final int index,
//            final char character) {
//            final Edge activeEdgeToSplit = this.getActiveEdge();
//            final Edge splittedEdge = new Edge(activeEdgeToSplit.getFrom(),
//                activeEdgeToSplit.getFrom() + this.activeLength,
//                nodeToAdd);
//            nodeToAdd.getEdges().put(word.charAt(activeEdgeToSplit.getFrom() + this.activeLength),
//                new Edge(activeEdgeToSplit.getFrom() + this.activeLength,
//                    activeEdgeToSplit.getTo(),
//                    activeEdgeToSplit.getNext()));
//            nodeToAdd.getEdges().put(character, new Edge(index, word.length(), null));
//            this.activeNode.getEdges().put(this.activeEdgeFirstCharacter, splittedEdge);
//        }
//
//        public Node setSlinkTo(final Node previouslyAddedNodeOrAddedEdgeNode,
//            final Node node) {
//            if (previouslyAddedNodeOrAddedEdgeNode != null) {
//                previouslyAddedNodeOrAddedEdgeNode.setSlink(node);
//            }
//            return node;
//        }
//
//        public Node setSlinkToActiveNode(final Node previouslyAddedNodeOrAddedEdgeNode) {
//            return setSlinkTo(previouslyAddedNodeOrAddedEdgeNode, this.activeNode);
//        }
//    }
//
//    private static int idGenerator;
//
//    private final String word;
//    private final Node root;
//    private ActivePoint activePoint;
//    private int remainder;
//
//    public ST(final String word) {
//        this.word = word;
//        this.root = new Node(idGenerator++);
//        this.activePoint = new ActivePoint(this.root, null, 0);
//        this.remainder = 0;
//        build();
//    }
//
//    private void build() {
//        for (int i = 0; i < this.word.length(); i++) {
//            add(i, this.word.charAt(i));
//        }
//    }
//
//    private void add(final int index, final char character) {
//        this.remainder++;
//        boolean characterFoundInTheTree = false;
//        Node previouslyAddedNodeOrAddedEdgeNode = null;
//        while (!characterFoundInTheTree && this.remainder > 0) {
//            if (this.activePoint.pointsToActiveNode()) {
//                if (this.activePoint.activeNodeHasEdgeStartingWith(character)) {
//                    activeNodeHasEdgeStartingWithCharacter(character, previouslyAddedNodeOrAddedEdgeNode);
//                    characterFoundInTheTree = true;
//                }
//                else {
//                    if (this.activePoint.activeNodeIs(this.root)) {
//                        rootNodeHasNotEdgeStartingWithCharacter(index, character);
//                    }
//                    else {
//                        previouslyAddedNodeOrAddedEdgeNode = internalNodeHasNotEdgeStartingWithCharacter(index,
//                            character, previouslyAddedNodeOrAddedEdgeNode);
//                    }
//                }
//            }
//            else {
//                if (this.activePoint.pointsToOnActiveEdge(this.word, character)) {
//                    activeEdgeHasCharacter();
//                    characterFoundInTheTree = true;
//                }
//                else {
//                    if (this.activePoint.activeNodeIs(this.root)) {
//                        previouslyAddedNodeOrAddedEdgeNode = edgeFromRootNodeHasNotCharacter(index,
//                            character,
//                            previouslyAddedNodeOrAddedEdgeNode);
//                    }
//                    else {
//                        previouslyAddedNodeOrAddedEdgeNode = edgeFromInternalNodeHasNotCharacter(index,
//                            character,
//                            previouslyAddedNodeOrAddedEdgeNode);
//                    }
//                }
//            }
//        }
//    }
//
//    private void activeNodeHasEdgeStartingWithCharacter(final char character,
//        final Node previouslyAddedNodeOrAddedEdgeNode) {
//        this.activePoint.setSlinkToActiveNode(previouslyAddedNodeOrAddedEdgeNode);
//        this.activePoint = this.activePoint.moveToEdgeStartingWithAndByOne(character);
//        if (this.activePoint.pointsToTheEndOfActiveEdge()) {
//            this.activePoint = this.activePoint.moveToNextNodeOfActiveEdge();
//        }
//    }
//
//    private void rootNodeHasNotEdgeStartingWithCharacter(final int index, final char character) {
//        this.activePoint.addEdgeToActiveNode(character, new Edge(index, this.word.length(), null));
//        this.activePoint = this.activePoint.moveTo(this.root);
//        this.remainder--;
//        assert this.remainder == 0;
//    }
//
//    private Node internalNodeHasNotEdgeStartingWithCharacter(final int index,
//        final char character,
//        Node previouslyAddedNodeOrAddedEdgeNode) {
//        this.activePoint.addEdgeToActiveNode(character, new Edge(index, this.word.length(), null));
//        previouslyAddedNodeOrAddedEdgeNode = this.activePoint.setSlinkToActiveNode(previouslyAddedNodeOrAddedEdgeNode);
//        if (this.activePoint.activeNodeHasSlink()) {
//            this.activePoint = this.activePoint.moveToSlink();
//        }
//        else {
//            this.activePoint = this.activePoint.moveTo(this.root);
//        }
//        this.remainder--;
//        return previouslyAddedNodeOrAddedEdgeNode;
//    }
//
//    private void activeEdgeHasCharacter() {
//        this.activePoint = this.activePoint.moveByOneCharacter();
//        if (this.activePoint.pointsToTheEndOfActiveEdge()) {
//            this.activePoint = this.activePoint.moveToNextNodeOfActiveEdge();
//        }
//    }
//
//    private Node edgeFromRootNodeHasNotCharacter(final int index,
//        final char character,
//        Node previouslyAddedNodeOrAddedEdgeNode) {
//        final Node newNode = new Node(idGenerator++);
//        this.activePoint.splitActiveEdge(this.word, newNode, index, character);
//        previouslyAddedNodeOrAddedEdgeNode = this.activePoint.setSlinkTo(previouslyAddedNodeOrAddedEdgeNode, newNode);
//        this.activePoint = this.activePoint.moveToEdgeStartingWithAndByActiveLengthMinusOne(this.root,
//            this.word.charAt(index - this.remainder + 2));
//        this.activePoint = walkDown(index);
//        this.remainder--;
//        return previouslyAddedNodeOrAddedEdgeNode;
//    }
//
//    private Node edgeFromInternalNodeHasNotCharacter(final int index,
//        final char character,
//        Node previouslyAddedNodeOrAddedEdgeNode) {
//        final Node newNode = new Node(idGenerator++);
//        this.activePoint.splitActiveEdge(this.word, newNode, index, character);
//        previouslyAddedNodeOrAddedEdgeNode = this.activePoint.setSlinkTo(previouslyAddedNodeOrAddedEdgeNode, newNode);
//        if (this.activePoint.activeNodeHasSlink()) {
//            this.activePoint = this.activePoint.moveToSlink();
//        }
//        else {
//            this.activePoint = this.activePoint.moveTo(this.root);
//        }
//        this.activePoint = walkDown(index);
//        this.remainder--;
//        return previouslyAddedNodeOrAddedEdgeNode;
//    }
//
//    private ActivePoint walkDown(final int index) {
//        while (!this.activePoint.pointsToActiveNode()
//            && (this.activePoint.pointsToTheEndOfActiveEdge() || this.activePoint.pointsAfterTheEndOfActiveEdge())) {
//            if (this.activePoint.pointsAfterTheEndOfActiveEdge()) {
//                this.activePoint = this.activePoint.moveToNextNodeOfActiveEdge(this.word, index);
//            }
//            else {
//                this.activePoint = this.activePoint.moveToNextNodeOfActiveEdge();
//            }
//        }
//        return this.activePoint;
//    }
//
//    public String toString(final String word) {
//        return this.root.toString(word);
//    }
//
//    public boolean contains(final String suffix) {
//        return this.root.contains(this.word, suffix);
//    }
//
//    public static void main(final String[] args) {
//        final String[] words = {
//                "abcabcabc$",
//                "abc$",
//                "abcabxabcd$",
//                "abcabxabda$",
//                "abcabxad$",
//                "aabaaabb$",
//                "aababcabcd$",
//                "ababcabcd$",
//                "abccba$",
//                "mississipi$",
//                "abacabadabacabae$",
//                "abcabcd$",
//                "00132220$"
//        };
//        Arrays.stream(words).forEach(word -> {
//            System.out.println("Building suffix tree for word: " + word);
//            final ST suffixTree = new ST(word);
//            System.out.println("Suffix tree: " + suffixTree.toString(word));
//            for (int i = 0; i < word.length() - 1; i++) {
//                assert suffixTree.contains(word.substring(i)) : word.substring(i);
//            }
//        });
//    }
//}